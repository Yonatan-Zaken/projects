/*************************
         EXT2
      C File
    Author : Yonatan Zaken
      Date : 05/04/2020          
*************************/
#include <sys/stat.h>       /* open                */
#include <fcntl.h>          /* for oflag constants */
#include <stdio.h>          /* printf              */
#include <stdlib.h>         /* malloc              */
#include <unistd.h>         /* close, read         */
#include <string.h>         /* memcpy              */
#include <ext2fs/ext2_fs.h> /* second extended filesystem */

#include "ext2.h"

#define BASE_OFFSET 1024                 
#define ROOT_INODE 2             
#define BLOCK_OFFSET(block) (BASE_OFFSET+(block-1)*block_size)

static unsigned int block_size = 0;       

typedef enum Indirection
{
    SINGLE = 1,
    DOUBLE,
    TRIPLE
} indirection_t;

/******************************** static functions ****************************/

static int OpenDevice(int fd, const char *device)
{
    if (0 > (fd = open(device, O_RDONLY, O_SYNC)))
    {
		perror(device);
		return FAIL;
	}
	
	return fd;    
}

/******************************************************************************/

static int ReadSuperBlock(int fd, struct ext2_super_block *super)
{
	lseek(fd, BASE_OFFSET, SEEK_SET); 
	read(fd, super, sizeof(*super));
	if (EXT2_SUPER_MAGIC != super->s_magic)
    {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		return NOT_EXT2;
	}
}

/******************************************************************************/

static void ReadGroupDesc(int fd, struct ext2_group_desc *group_des, size_t offset)
{
	lseek(fd, BASE_OFFSET + offset, SEEK_SET);
	read(fd, group_des, sizeof(*group_des));
}

/******************************************************************************/

static void ReadInode(int fd, size_t inode_num , const struct ext2_group_desc *group, struct ext2_inode *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table) +
    (inode_num - 1) * sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

/******************************************************************************/

static void ReadBlock(int fd, size_t block_num, void *dir)
{
	lseek(fd, BLOCK_OFFSET(block_num), SEEK_SET);
    read(fd, dir, block_size);
}

/******************************************************************************/

static void PrintSB(const struct ext2_super_block super, const char *device)
{
    block_size = 1024 << super.s_log_block_size;
	printf("Reading super-block from device %s:\n"
       "Inodes count            : %u\n"
       "Blocks count            : %u\n"
       "Reserved blocks count   : %u\n"
       "Free blocks count       : %u\n"
       "Free inodes count       : %u\n"
       "First data block        : %u\n"
       "Block size              : %u\n"
       "Blocks per group        : %u\n"
       "Inodes per group        : %u\n"
       "Creator OS              : %u\n"
       "First non-reserved inode: %u\n"
       "Size of inode structure : %hu\n\n"
       ,
       device,
       super.s_inodes_count,  
       super.s_blocks_count,
       super.s_r_blocks_count,     
       super.s_free_blocks_count,
       super.s_free_inodes_count,
       super.s_first_data_block,
       block_size,
       super.s_blocks_per_group,
       super.s_inodes_per_group,
       super.s_creator_os,
       super.s_first_ino,          
       super.s_inode_size); 
}

/******************************************************************************/

static void PrintGD(const struct ext2_group_desc group, size_t i)
{
    printf("Reading group %lu descriptor from device:\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n\n"
	       ,i + 1,
	       group.bg_block_bitmap,
	       group.bg_inode_bitmap,
	       group.bg_inode_table,
	       group.bg_free_blocks_count,
	       group.bg_free_inodes_count,
	       group.bg_used_dirs_count);        
}

/******************************************************************************/

static void RecIndirection(int fd, size_t block_number, indirection_t indirection_level)
{
    size_t entry_count = 0;
    __u32 *entry = NULL;
    char *buffer = NULL;
    char *text_holder = NULL;
    
    if (0 == block_number)
    {
        return;
    }
    
    if (0 == indirection_level)
    {
        if (NULL == (text_holder = (char *)malloc(sizeof(char) * block_size)))
        {
            exit(1);
        }
        
        ReadBlock(fd, block_number, text_holder);
        printf("%s", text_holder);
        free(text_holder); text_holder = NULL;
        
        return;
    }
    
    if (NULL == (buffer = (char *)malloc(block_size)))
    {
        exit(1);    
    }
    
    ReadBlock(fd, block_number, buffer);
    entry_count = block_size / sizeof(*entry);
    
    for (entry = (__u32 *)buffer; --entry_count; ++entry)
    {
        if (0 != *entry)
        {
            RecIndirection(fd, *entry, indirection_level - 1);
        }
    }
    
    free(buffer); buffer = NULL;
    return;
}

/******************************************************************************/

static void PrintFile(int fd, const struct ext2_inode* inode)
{
    size_t i = 0;
    size_t j = 0;
    size_t file_size = inode->i_size;
    char *buffer = malloc(sizeof(char) * block_size);
    
    printf("\ni_size: %u\n", inode->i_size);
    printf("\ni_blocks: %u\n", inode->i_blocks);
    
    for (i = 0; i < (inode->i_blocks) / 2 ; ++i)
    {
        ReadBlock(fd, inode->i_block[i], buffer);
        if (EXT2_NDIR_BLOCKS > i)
        {
            printf("%s", buffer);             
        }
        
        else if (EXT2_IND_BLOCK == i)
        {
            RecIndirection(fd, inode->i_block[i], SINGLE);
        }
        
        else if (EXT2_DIND_BLOCK == i)
        {
            RecIndirection(fd, inode->i_block[i], DOUBLE);    
        }
        
        else if (EXT2_TIND_BLOCK == i)
        {
            RecIndirection(fd, inode->i_block[i], TRIPLE);
        }
    }
    
    free(buffer); buffer = NULL;
}

/******************************************************************************/

static void *TraverseDir(const struct ext2_inode *inode, struct ext2_dir_entry_2 *dir_entry, const char *user_file)
{
    size_t size = 0;
    char file_name[EXT2_NAME_LEN+1] = {0};
    
    while((size < inode->i_size) && dir_entry->inode)
    {
        memcpy(file_name, dir_entry->name, dir_entry->name_len);
        file_name[dir_entry->name_len] = '\0';
        printf("\nname len: %u file name:%s dir_len:%u inode:%u\n\n", 
               dir_entry->name_len, file_name, dir_entry->rec_len, dir_entry->inode);
        if (0 == strcmp(file_name, user_file))
        {
            break;
        }
        dir_entry = (void*)((char*)dir_entry + dir_entry->rec_len);
        size += dir_entry->rec_len;
        memset(file_name, '\0', EXT2_NAME_LEN + 1);
    }
    
    return dir_entry;
}

/******************************************************************************/

static void SearchFile(int fd, struct ext2_group_desc *group, struct ext2_inode *inode, const char *user_file, __u32 inodes_per_grp)
{
    char *token = NULL;
    char *path = NULL;
    char temp[EXT2_NAME_LEN + 1] = {0};
    struct ext2_dir_entry_2 *dir_entry = NULL;
    struct ext2_dir_entry_2 *holder = NULL;
    
	if (NULL == (dir_entry = malloc(block_size)))
	{
		fprintf(stderr, "Memory error\n");
		close(fd);
		exit(1);
	}
	
	holder = dir_entry;
	ReadBlock(fd, inode->i_block[0], dir_entry);
    path = strchr(user_file, '/') + 1;
    strcpy(temp, path);
    token = strtok(temp, "/");     
    token = strtok(NULL, "/");
    
    dir_entry = TraverseDir(inode, dir_entry, token);
    ReadGroupDesc(fd, group, (dir_entry->inode / inodes_per_grp) * sizeof(*group) 
    + block_size);
    ReadInode(fd, dir_entry->inode - (dir_entry->inode / inodes_per_grp) * inodes_per_grp, group, inode);
    
    if (!S_ISDIR(inode->i_mode))
    {
        ReadGroupDesc(fd, group, (dir_entry->inode / inodes_per_grp) * sizeof(*group) 
        + block_size);
        ReadInode(fd, dir_entry->inode - 
        (dir_entry->inode / inodes_per_grp) * inodes_per_grp, group, inode);
        free(holder);
                
        return;
    }
    
    free(holder);
    SearchFile(fd, group, inode, path, inodes_per_grp);
}

/******************************* API Functions*********************************/

int PrintSuperBlock(const char *device)
{
    int fd = 0;
    struct ext2_super_block super = {0};
    
    if (FAIL == (fd = OpenDevice(fd, device)))
    {
        return FAIL;
    }
    
	if (FAIL == ReadSuperBlock(fd, &super))
	{
	    close(fd);
	    return FAIL;    
	}  
	
    close(fd);
    PrintSB(super, device);
    
    return SUCCESS;
}

/******************************************************************************/

int PrintGroupDescriptors(const char *device)
{
    size_t i = 0;
    int fd = 0;
    size_t group_count = 0;
    struct ext2_super_block super = {0};
    struct ext2_group_desc group = {0};
    
    if (FAIL == (fd = OpenDevice(fd, device)))
    {
        return FAIL;
    }
    
	if (FAIL == ReadSuperBlock(fd, &super))
	{
	    close(fd);
	    return FAIL;
	}
	
	group_count = super.s_blocks_count / super.s_blocks_per_group;
	for (i = 0; i < group_count; ++i)
	{
	    ReadGroupDesc(fd, &group, block_size + i * sizeof(struct ext2_group_desc));
        PrintGD(group, i);     
	}
	
	close(fd);
	return SUCCESS;
}

/******************************************************************************/

int PrintFileContent(const char *device, const char *filename)
{
    int fd = 0;
    __u32 inodes_per_grp = 0;
    struct ext2_super_block super = {0};
    struct ext2_group_desc group = {0}; 
    struct ext2_inode inode = {0};
    
    if (FAIL == (fd = OpenDevice(fd, device)))
    {
        return FAIL;
    }
     
	if (NOT_EXT2 == ReadSuperBlock(fd, &super))
	{
	    close(fd);
	    return NOT_EXT2;
	}
	
	inodes_per_grp = super.s_inodes_per_group;
    block_size = 1024 << super.s_log_block_size;
    
    ReadGroupDesc(fd, &group, block_size);
	ReadInode(fd, ROOT_INODE, &group, &inode);
	SearchFile(fd, &group, &inode, filename, inodes_per_grp);
    PrintFile(fd, &inode);
    
	close(fd);
	
	return SUCCESS;
}
