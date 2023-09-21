#include "ext2fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define IMAGE "simple-testcase-MKDIR1/MKDIR_baseline1.img" ////// just for testing do not use it

#define BASE_OFFSET 1024  /* location of the super-block in the first group */

#define BLOCK_OFFSET(block) ((block)*block_size)

struct ext2_dir_entry** get_dir_entries(struct ext2_inode *inode);
struct ext2_dir_entry *find_dir_entry_by_name(struct ext2_dir_entry **entries, const char *name);

int fd, block_size, block_p_group;
struct ext2_super_block *super_block;
struct ext2_block_group_descriptor *group_desc;
unsigned char *block_bitmap, *inode_bitmap;

void get_super_block()
{
    super_block = malloc(sizeof(struct ext2_super_block));
    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, super_block, sizeof(struct ext2_super_block));
    block_size = EXT2_UNLOG(super_block->log_block_size);
    block_p_group = super_block->blocks_per_group;
}

void get_1st_group_desc()
{
    group_desc = malloc(sizeof(struct ext2_block_group_descriptor));
    int read_start = BASE_OFFSET < block_size ? block_size : BASE_OFFSET + block_size;
    lseek(fd, read_start, SEEK_SET);
    read(fd, group_desc, sizeof(struct ext2_block_group_descriptor));
}

void get_block_bitmap()
{
    block_bitmap = malloc(block_size);
    lseek(fd, BLOCK_OFFSET(group_desc->block_bitmap), SEEK_SET);
    read(fd, block_bitmap, block_size);
}

void get_inode_bitmap()
{
    inode_bitmap = malloc(block_size);
    lseek(fd, BLOCK_OFFSET(group_desc->inode_bitmap), SEEK_SET);
    read(fd, inode_bitmap, block_size);
}

int count_slashes(const char *path)
{
    int slash_count = 0;
    for (int i = 0; i < strlen(path); ++i)
    {
        if (path[i] == '/')
        {
            ++slash_count;
        }
    }
    return slash_count;
}

void normalize_path(char *path)
{
    int read = 0, write = 0;
    while (path[read] != '\0')
    {
        if (path[read] != '/' || path[read + 1] != '/')
        {
            path[write++] = path[read];
        }
        ++read;
    }
    path[write] = '\0';
}

void split_path(char *path, char *parent_path, char *name)
{
    // copy path to temp_path to be able to modify it
    char *temp_path = malloc(strlen(path) + 1);
    strcpy(temp_path, path);

    normalize_path(temp_path);

    if(count_slashes(temp_path) == 1)
    {
        strcpy(parent_path, "/");
        strcpy(name, temp_path+1);
        strcpy(path, temp_path);
        return;
    }

    char *last_slash = strrchr(temp_path, '/');
  
    // copy everything before the slash to parent_path
    size_t parent_length = last_slash - temp_path;
    strncpy(parent_path, temp_path, parent_length);
    parent_path[parent_length] = '\0';

    // copy everything after the slash to name
    strcpy(name, last_slash + 1);

    strcpy(path, temp_path);
    free(temp_path);
}

char **split_path_into_components(const char *path)
{
    int slash_count = count_slashes(path);

    if(slash_count == 1)
    {
        char **components = malloc(sizeof(char*) * 2);
        components[0] = strdup(path + 1);
        components[1] = NULL;
        return components;
    }

    char **components = malloc(sizeof(char*) * (slash_count + 1));
    char *path_copy = strdup(path);

    char *token = strtok(path_copy, "/");;
    int i = 0;
    while (token != NULL)
    {
        components[i++] = strdup(token); // allocate and copy component
        token = strtok(NULL, "/");
    }
    components[i] = NULL;
    return components;
}

struct ext2_inode *get_inode(uint32_t inode_num)
{
    // calculate which block group the inode is in
    uint32_t block_group = (inode_num - 1) / super_block->inodes_per_group;
    // calculate the index within the block group
    uint32_t index = (inode_num - 1) % super_block->inodes_per_group;
    // calculate the offset
    uint32_t offset = group_desc[block_group].inode_table * block_size + (index * super_block->inode_size);

    struct ext2_inode inode;

    lseek(fd, offset, SEEK_SET);
    read(fd, &inode, sizeof(struct ext2_inode));

    struct ext2_inode *inode_copy = malloc(sizeof(struct ext2_inode));

    memcpy(inode_copy, &inode, sizeof(struct ext2_inode));
    return inode_copy;
}

struct ext2_dir_entry **get_dir_entries(struct ext2_inode *inode)
{
    // check if it is a directory (?)
    if ((inode->mode & 0xF000) != EXT2_I_DTYPE)
    {
        return NULL;
    }

    // read direct
    struct ext2_dir_entry **entries = calloc(12 * block_size / sizeof(struct ext2_dir_entry), sizeof(struct ext2_dir_entry*));
    int entry_number = 0;

    for (int i = 0; i < 12; i++)
    {
	    if (inode->direct_blocks[i] == 0) continue;

    	off_t entry_offset = BLOCK_OFFSET(inode->direct_blocks[i]);
    	while( entry_offset != BLOCK_OFFSET(inode->direct_blocks[i] + 1))
    	{
		    struct ext2_dir_entry entry;
    		lseek(fd, entry_offset, SEEK_SET);
    		read(fd, &entry, sizeof(struct ext2_dir_entry));
		    entries[entry_number] = calloc(1, sizeof(struct ext2_dir_entry) + entry.name_length + 1);
		    memcpy(entries[entry_number], &entry, sizeof(struct ext2_dir_entry));
		    read(fd, entries[entry_number]->name, entry.name_length);
    		entry_offset += entry.length;
    	    entry_number++;
    	}
    }

    entries = realloc(entries, sizeof(struct ext2_dir_entry*) * (entry_number + 1));
    entries[entry_number] = NULL;
    return entries;
}

struct ext2_dir_entry *find_dir_entry_by_name(struct ext2_dir_entry **entries, const char *name)
{
    for(int i = 0; entries && entries[i] != NULL; ++i)
    {
        if (strncmp(entries[i]->name, name, entries[i]->name_length) == 0)
        {
            return entries[i];
        }
    }

    return NULL;
}

struct ext2_inode *get_inode_from_path(const char *path)
{
    uint32_t inode_num = EXT2_ROOT_INODE; // starting with the root inode

    // split the path into components
    int i = strlen(path);
    char *temp_path = malloc(i + 1);
    strcpy(temp_path, path);
    char **components = split_path_into_components(temp_path);

    if(components[0] == NULL || !components)
    {
        return NULL;
    }

    for (int i = 0; components[i] != NULL; ++i)
    {
        struct ext2_inode *inode = get_inode(inode_num);

        if (inode == NULL)
        {
            // the inode doesn't exist, cleanup and return NULL
            for (int j = 0; components[j] != NULL; ++j)
            {
                free(components[j]);
            }
            free(components);
            return NULL;
        }

        struct ext2_dir_entry **entries = get_dir_entries(inode);

        if (entries == NULL)
        {
            // the inode is not a directory, cleanup and return NULL
            for (int j = 0; components[j] != NULL; ++j)
            {
                free(components[j]);
            }
            free(components);
            return NULL;
        }

        // search for the current component in the directory entries
        struct ext2_dir_entry *entry = find_dir_entry_by_name(entries, components[i]);

        if (entry == NULL)
        {
            // no directory entry with the same name found, the path doesn't exist
            for (int j = 0; components[j] != NULL; ++j)
            {
                free(components[j]);
            }
            free(components);
            return NULL;
        }
        // set the inode_num for the next iteration to the inode number of the found directory entry
        inode_num = entry->inode;

        // free the entries memory as it's not needed anymore
        free(entries);
    }

    // cleanup components array
    for (int i = 0; components[i] != NULL; ++i)
    {
        free(components[i]);
    }
    free(components);
    return get_inode(inode_num);
}

bool path_exists(char *path)
{
    struct ext2_inode *inode = get_inode_from_path(path);
    bool exists = (strcmp(path, "/") == 0) || inode != NULL;
    free(inode);
    return exists;
}

////////////////////////////////////////////////////////////////////////////////////////////

// find a new inode for the new directory
int get_free_inode() /////////////// ????????
{
    // find a free inode
    for (int i = 0; i < block_size; ++i)
    {
        if (inode_bitmap[i] == 0)
        {
            // found a free inode
            inode_bitmap[i] = 1;
            group_desc->free_inode_count--;
            return i + 1;
        }
    }
    return 0;
}

// allocate the new inode for the new directory
struct ext2_inode* allocate_inode(int inode_no) /////////////// ????????
{
    struct ext2_inode* inode = get_inode(inode_no);

    inode->mode = EXT2_I_FTYPE | EXT2_I_FPERM;
    inode->uid = EXT2_I_UID;
    inode->size = 0;
    inode->access_time = inode->creation_time = inode->modification_time = time(NULL);
    inode->deletion_time = 0;
    inode->gid = EXT2_I_GID;
    inode->link_count = 1;
    inode->block_count_512 = 0;
    inode->flags = 0;

    for(int i=0; i<EXT2_NUM_DIRECT_BLOCKS; i++)
    {
        inode->direct_blocks[i] = 0;
    }

    inode->single_indirect = 0;
    inode->double_indirect = 0;
    inode->triple_indirect = 0; 

    return inode;
}

// allocate a new block for the new directory
uint32_t allocate_block() //////////////////////////////// ????????
{
    // find a free block
    for (int i = 0; i < block_size; ++i)
    {
        if (block_bitmap[i] == 0)
        {
            // found a free block
            block_bitmap[i] = 1;
            group_desc->free_block_count--;
            return i + 1;
        }
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////

void ext2_mkdir(char *path)
{
    // split the path into parent_path and name
    char *parent_path, *name;
    
    parent_path = malloc(strlen(path) + 1);
    name = malloc(strlen(path) + 1);
    
    split_path(path, parent_path, name);

    // check if parent_path exists and path doesn't
    if (path_exists(parent_path) && !path_exists(path))
    {
        // get the inode of the parent_path
        struct ext2_inode *parent_inode = get_inode_from_path(parent_path);

        // create a new inode for the new directory
        int inode_no = get_free_inode();
        if (inode_no == 0) return;
        printf("EXT2_ALLOC_INODE %d\n", inode_no);

        // struct ext2_inode *inode = get_inode(inode_no);

        // allocate a new block for the new directory
        uint32_t block_no = allocate_block();
        if (block_no == 0) return;
        // struct 
        printf("EXT2_ALLOC_BLOCK %d\n", block_no);
        printf("EXT2_ALLOC_ENTRY \".\" %d\n", block_no);
        printf("EXT2_ALLOC_ENTRY \"..\" %d\n", block_no);
        printf("EXT2_ALLOC_ENTRY \"%s\"\n", name);

        // link the block to the new inode
        // inode->direct_blocks[0] = block_no;

        // create a dir entry with name under parent inode
        
        // link the created dir entry to the new inode

        // create a dir entry with name "." under new inode

        // link the created dir entry to the new inode

        // create a dir entry with name ".." under new inode

        // link the created dir entry to the parent inode

        // reverse through parent inode to root inode

        // update their modification and access times
    }

    // free dynamically allocated memory
    free(parent_path);
    free(name);
}

void ext2_ls(char *path)
{
    // split the path into parent_path and name
    normalize_path(path);

    // check if path exists
    if (path_exists(path))
    {
        // get the inode of the path
        struct ext2_inode *inode = get_inode_from_path(path);

        // check if the inode is a directory
        if (inode->mode & EXT2_I_FTYPE == EXT2_I_FTYPE)
        {
            // get the directory entries
            struct ext2_dir_entry **entries = get_dir_entries(inode);

            // print the directory entries
            for (int i = 0; entries[i] != NULL; ++i)
            {
                if ((strcmp(entries[i]->name, ".") != 0) && (strcmp(entries[i]->name, "..") != 0))
                {
                    printf("%s\n", entries[i]->name);
                }
            }

            // free the entries memory
            free(entries);
        }
        else
        {
            printf("Not a directory.\n");
        }

        // free the inode memory
        free(inode);
    }
    else
    {
        printf("Path doesn't exist.\n");
    }
}


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s FS_IMAGE command /abs/path/to/dirname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDWR);
    if (fd == 0)
    {
        printf("Failed to open the disk image file.\n");
        exit(EXIT_FAILURE);
    }

    char* command = strdup(argv[2]);
    char* path = strdup(argv[3]);

    get_super_block();
    get_1st_group_desc();
    get_inode_bitmap();
    get_block_bitmap();

    // const char *literal = "///////kk";
    // char *path = malloc(strlen(literal) + 1);
    // strcpy(path, literal);

    char *parent_path, *name;
    parent_path = malloc(strlen(path) + 1);
    name = malloc(strlen(path) + 1);

    split_path(path, parent_path, name);

    char** compList;
    compList = split_path_into_components(path);

    // printf("-------------------- \n");

    // printf("path: %s \n", path);
    // printf("parent: %s \n", parent_path);
    // printf("%s \n", name);

    // printf("-------------------- \n");

    // for (int i = 0; compList[i] != NULL; ++i)
    // {
    //     printf("comps[%d]: %s \n", i, compList[i]);
    // }

    // printf("-------------------- \n");

    // printf("super_block->inode_count: %d\n", super_block->inode_count);
    // printf("super_block->block_count: %d\n", super_block->block_count);
    // printf("super_block->blocks_per_group: %d\n", super_block->blocks_per_group);
    // printf("super_block->inodes_per_group: %d\n", super_block->inodes_per_group);
    // printf("super_block->first_data_block: %d\n", super_block->first_data_block);
    // printf("super_block->log_block_size: %d\n", super_block->log_block_size);

    // printf("-------------------- \n");

    struct ext2_inode *inode = get_inode(EXT2_ROOT_INODE);

    // for (int i = 0; i < 12; ++i)
    // {
    //     printf("inode->i_block[%d]: %d\n", i, inode->direct_blocks[i]);
    // }
    // printf("inode->i_block[SINGLE]: %d\n", inode->single_indirect);
    // printf("inode->i_block[DOUBLE]: %d\n", inode->double_indirect);
    // printf("inode->i_block[TRIPLE]: %d\n", inode->triple_indirect);

    // printf("inode->i_uid: %d\n", inode->uid);
    // printf("inode->i_size: %d\n", inode->size);
    // printf("inode->mode: %d\n", inode->mode & 0xF000);


    // printf("-------------------- \n");

    // printf("group_desc->block_bitmap: %d\n", group_desc->block_bitmap);
    // printf("group_desc->inode_bitmap: %d\n", group_desc->inode_bitmap);
    // printf("group_desc->inode_table: %d\n", group_desc->inode_table);
    // printf("group_desc->used_dirs_count: %d\n", group_desc->used_dirs_count);

    // printf("-------------------- \n");

    // struct ext2_dir_entry **entries = get_dir_entries(inode);
    // for(int i = 0; entries[i] != NULL; ++i)
    // {
    //     printf("entries[%d]->name: %s\n", i, entries[i]->name);
    //     printf("entries[%d]->inode: %d\n", i, entries[i]->inode);
    // }

    // printf("-------------------- \n");

    // struct ext2_dir_entry *entry = find_dir_entry_by_name(entries, "man.d");
    // printf("entry->name: %s\n", entry->name);
    // printf("entry->inode: %d\n", entry->inode);

    // entry = find_dir_entry_by_name(entries, "lost+found");
    // printf("entry->name: %s\n", entry->name);
    // printf("entry->inode: %d\n", entry->inode);

    // entry = find_dir_entry_by_name(entries, "foo");
    // printf("entry->name: %s\n", entry->name);
    // printf("entry->inode: %d\n", entry->inode);

    // printf("-------------------- \n");

    // struct ext2_inode *inode2 = get_inode_from_path("/foo");
    // if(inode2)
    // {
    //     printf("inode2->i_uid: %d\n", inode2->uid);
    //     printf("inode2->i_size: %d\n", inode2->size);
    //     printf("inode2->mode: %d\n", inode2->mode & 0xF000);
    // }

    // printf("-------------------- \n");

    // if(path_exists(parent_path))
    // {
    //     printf("path exists \n");
    // }
    // else
    // {
    //     printf("path does not exist \n");
    // }

    // printf("------- ls ------- \n");

    if(strcmp(command, "ls") == 0)
    {
        ext2_ls(path);
    }

    // printf("------- ls ------- \n");

    // printf("------- mkdir ------- \n");

    if(strcmp(command, "mkdir") == 0)
    {
        ext2_mkdir(path);
    }

    // printf("------- mkdir -------\n");
    

    close(fd);

    free(command);
    free(path); 
    free(parent_path);
    free(name);

    return 0;
}
