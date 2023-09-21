#include "ext2fs.h"
#include "ext2fs_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

char *get_time_format(const uint32_t t)
{
    const time_t t2 = (const long)t;
    return strtok(asctime(localtime(&t2)), "\n");

}

void print_stat(struct stat *st) {
    printf("###############################\n");
    printf("# File attributes:\n");
    printf("# Mode: %lo\n", (unsigned long) st->st_mode);
    printf("# Owner UID: %d\n", st->st_uid);
    printf("# Owner GID: %d\n", st->st_gid);
    printf("# Size: %ld bytes\n", st->st_size);
    printf("# Last access time:\n# %25s\n",
           get_time_format(st->st_atime));
    printf("# Last modification time:\n# %25s\n",
           get_time_format(st->st_mtime));
    printf("# Last status change time:\n# %25s\n",
           get_time_format(st->st_ctime));
    printf("# Number of hard links: %ld\n", st->st_nlink);
    printf("# Device ID (if special file): %ld\n", st->st_rdev);
    printf("# Inode number: %ld\n", st->st_ino);
    printf("# File system ID: %ld\n", st->st_dev);
    printf("###############################\n\n");
}

void print_super_block(struct ext2_super_block *super_block)
{
    printf("###############################\n");
    printf("#   EXT2 SUPER BLOCK DETAILS  #\n");
    printf("# inode_count: %-14u #\n", super_block->inode_count);
    printf("# block_count: %-14u #\n", super_block->block_count);
    printf("# reserved_block_count: %-5u #\n", super_block->reserved_block_count);
    printf("# free_block_count: %-9u #\n", super_block->free_block_count);
    printf("# free_inode_count: %-9u #\n", super_block->free_inode_count);
    printf("# first_data_block: %-9u #\n", super_block->first_data_block);
    printf("# log_block_size: %-11u #\n", super_block->log_block_size);
    printf("# log_fragment_size: %-8u #\n", super_block->log_fragment_size);
    printf("# blocks_per_group: %-9u #\n", super_block->blocks_per_group);
    printf("# fragments_per_group: %-6u #\n", super_block->fragments_per_group);
    printf("# inodes_per_group: %-9u #\n", super_block->inodes_per_group);
    printf("# mount_time: %-15u #\n", super_block->mount_time);
    printf("# write_time: %-15u #\n# %-27s #\n", super_block->write_time,
		                                 get_time_format(super_block->write_time));
    printf("# mount_count: %-14hu #\n", super_block->mount_count);
    printf("# max_mount_count: %-10hu #\n", super_block->max_mount_count);
    printf("# magic: %-20hu #\n", super_block->magic);
    printf("# state: %-20hu #\n", super_block->state);
    printf("# errors: %-19hu #\n", super_block->errors);
    printf("# minor_rev_level: %-10hu #\n", super_block->minor_rev_level);
    printf("# last_check_time: %-10u #\n# %-27s #\n", super_block->last_check_time, 
		                                      get_time_format(super_block->last_check_time));
    printf("# check_interval: %-11u #\n", super_block->check_interval);
    printf("# creator_os: %-15u #\n", super_block->creator_os);
    printf("# rev_level: %-16u #\n", super_block->rev_level);
    printf("# default_uid: %-14hu #\n", super_block->default_uid);
    printf("# default_gid: %-14hu #\n", super_block->default_gid);
    printf("# first_inode: %-14u #\n", super_block->first_inode);
    printf("# inode_size: %-15hu #\n", super_block->inode_size);
    printf("# block_group_nr: %-11hu #\n", super_block->block_group_nr);
    printf("# feature_compat: %-11u #\n", super_block->feature_compat);
    printf("# feature_incompat: %-9u #\n", super_block->feature_incompat);
    printf("# feature_ro_compat: %-8u #\n", super_block->feature_ro_compat);
    printf("###############################\n");
    printf("\n");
}


void print_group_descriptor(struct ext2_block_group_descriptor *group_descriptor)
{
	printf("###############################\n");
	printf("# EXT2 BLOCK GROUP DESCRIPTOR #\n");
	printf("# block_bitmap : %-12u #\n", group_descriptor->block_bitmap);
	printf("# inode_bitmap : %-12u #\n", group_descriptor->inode_bitmap);
	printf("# inode_table: %-14u #\n", group_descriptor->inode_table);
	printf("# free_block_count : %-8hu #\n", group_descriptor->free_block_count);
	printf("# free_inode_count : %-8hu #\n", group_descriptor->free_inode_count);
	printf("# used_dirs_count: %-10hu #\n", group_descriptor->used_dirs_count);
	printf("# pad: %-22hu #\n", group_descriptor->pad);
	printf("###############################\n");
	printf("\n");
}

void print_dir_entry(struct ext2_dir_entry *dir, const char* dir_name)
{
	printf("###############################\n");
	printf("# EXT2 DIRECTORY ENTRY        #\n");
	printf("# inode : %-19u #\n", dir->inode);
	printf("# length : %-18hu #\n", dir->length);
	printf("# name_length: %-14hhu #\n", dir->name_length);
	printf("# file_type : %-15hhu #\n", dir->file_type);
	printf("# name : %-20s #\n", dir_name);
	printf("###############################\n");
	printf("\n");
}

void print_inode(const struct ext2_inode *inode, int index)
{
    char mode[50] = {'\0'};
    switch (inode->mode & 0xf000) 
    {
	    case 0xC000: strcpy(mode, "socket"); break;
	    case 0xA000: strcpy(mode, "symbolic link"); break;
	    case EXT2_I_FTYPE: strcpy(mode, "regular file"); break;
	    case 0x6000: strcpy(mode, "block device"); break;
	    case EXT2_I_DTYPE: strcpy(mode, "directory"); break;
	    case 0x2000: strcpy(mode, "character device"); break;
	    case 0x1000: strcpy(mode, "fifo"); break;
	    default:     sprintf(mode, "0x%x", inode->mode); break;
    }

    printf("###############################\n");
    printf("#    EXT2 INODE DETAILS %-2d    #\n", index);
    printf("# mode: 0x%3x %-15s #\n", 0xfff & inode->mode, mode);
    printf("# uid: %-22hu #\n", inode->uid);
    printf("# size: %-21u #\n", inode->size);
    printf("# access_time: %-14u #\n", inode->access_time);
    if (inode->access_time != 0u)
	    printf("# %-27s #\n", get_time_format(inode->access_time));
    printf("# creation_time: %-12u #\n", inode->creation_time);
    if (inode->creation_time != 0u)
	    printf("# %-27s #\n", get_time_format(inode->creation_time));
    printf("# modification_time: %-8u #\n", inode->modification_time);
    if (inode->modification_time != 0u)
	    printf("# %-27s #\n", get_time_format(inode->modification_time));
    printf("# deletion_time: %-12u #\n", inode->deletion_time);
    if (inode->deletion_time != 0u)
	    printf("# %-27s #\n", get_time_format(inode->deletion_time));
    printf("# gid: %-22hu #\n", inode->gid);
    printf("# link_count: %-15hu #\n", inode->link_count);
    printf("# block_count_512: %-10u #\n", inode->block_count_512);
    printf("# flags: %-20u #\n", inode->flags);
    printf("# reserved: %-17u #\n", inode->reserved);
    
    printf("# direct_blocks:              #\n");
    for (int i = 0; i < EXT2_NUM_DIRECT_BLOCKS; i++) {
        printf("#   direct_blocks[%2d]: %-6u #\n", i + 1, inode->direct_blocks[i]);
    }
    
    printf("# single_indirect: %-10u #\n", inode->single_indirect);
    printf("# double_indirect: %-10u #\n", inode->double_indirect);
    printf("# triple_indirect: %-10u #\n", inode->triple_indirect);
    
    printf("###############################\n");
    printf("\n");
}

