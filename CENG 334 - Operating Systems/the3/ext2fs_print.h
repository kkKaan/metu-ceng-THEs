#ifndef __EXT2_SNAP_JOURNAL__EXT2FS_DEBUG__
#define __EXT2_SNAP_JOURNAL__EXT2FS_DEBUG__

#include "ext2fs.h"
#include <sys/stat.h>

#define CEIL(num, denom) ((num) / (denom) + ((num) % (denom) ? 1U : 0U))
#define EXT2_DIR_LENGTH(name_length) (sizeof(struct ext2_dir_entry) + CEIL(name_length, 4U) * 4U)

#ifdef EXT2_DEBUG
#define ext2_debug(f, a...)                              \
    {                                                    \
        fprintf(stderr, "EXT2S-fs DEBUG (%s, %d): %s: ", \
                __FILE__, __LINE__, __func__);           \
        fprintf(stderr, f, ##a);                         \
    }
#else
#define ext2_debug(f, a...) /**/
#endif


#define ext2_perror(str)                                 \
{                                                        \
    perror(str);				         \
    fprintf(stderr, "[%s:%d]: %s: ",     		 \
            __FILE__, __LINE__, __func__);               \
}


void print_stat(struct stat *st);
void print_super_block(struct ext2_super_block *super_block);
void print_group_descriptor(struct ext2_block_group_descriptor *group_descriptor);
void print_dir_entry(struct ext2_dir_entry *dir, const char* dir_name);
void print_inode(const struct ext2_inode *inode, int index);

#endif
