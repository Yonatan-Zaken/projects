#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ext2fs/ext2_fs.h>

#define FAIL 1
#define SUCCESS 0

#define BASE_OFFSET 1024
#define BLOCK_SIZE 1024                   
#define ROOT_INODE 2          
#define FD_DEVICE "/dev/fd0"    
#define BLOCK_OFFSET(block) (BASE_OFFSET+(block-1)*block_size)

static unsigned int block_size = 0;       
char buffer[50] = {0};
/******************************** static functions ****************************/

static int OpenDevice(int fd, const char *device)
{
    if ((fd = open(device, O_RDONLY)) < 0)
    {
		perror(FD_DEVICE);
		exit(1);  /* error while opening the floppy device */
	}
	
	return fd;    
}

static void ReadSuperBlock(struct ext2_super_block *super, int fd)
{
	lseek(fd, BASE_OFFSET, SEEK_SET); 
	read(fd, super, sizeof(*super));
}

static void ReadGroupDesc(struct ext2_group_desc *group_des, int fd, size_t offset)
{
	lseek(fd, BASE_OFFSET + offset, SEEK_SET);
	read(fd, group_des, sizeof(*group_des));
}

void ReadInode(int fd, size_t inode_num ,const struct ext2_group_desc *group, struct ext2_inode *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table) +
    (inode_num - 1) * sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

static void PrintSB(struct ext2_super_block super)
{
    block_size = 1024 << super.s_log_block_size;
	printf("Reading super-block from device " FD_DEVICE ":\n"
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

static void PrintGD(struct ext2_group_desc group, size_t i)
{
    printf("Reading group %lu descriptor from device " FD_DEVICE ":\n"
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

int PrintSuperBlock(const char *device)
{
    int fd = 0;

    struct ext2_super_block super = {0};
    
    fd = OpenDevice(fd, device);
	ReadSuperBlock(&super, fd);
    close(fd);

	if (super.s_magic != EXT2_SUPER_MAGIC)
    {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(FAIL);
	}

    PrintSB(super);
    
    return SUCCESS;
}

int PrintGroupDescriptors(const char *device)
{
    size_t i = 0;
    int fd = 0;
    size_t group_count = 0;
    struct ext2_super_block super = {0};
    struct ext2_group_desc group = {0};
    
    fd = OpenDevice(fd, device);
	ReadSuperBlock(&super, fd);
	
	if (super.s_magic != EXT2_SUPER_MAGIC)
    {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(FAIL);
	}
	
	group_count = super.s_blocks_count / super.s_blocks_per_group;;
	block_size = 1024 << super.s_log_block_size;
	
	for (i = 0; i < group_count; ++i)
	{
	    ReadGroupDesc(&group, fd, block_size + i * sizeof(struct ext2_group_desc));
        PrintGD(group, i);     
	}
	
	close(fd);
	return SUCCESS;
}

int PrintFileContent(const char *device, const char *filename)
{
    int fd = 0;
    size_t size = 0;
    size_t group_count = 0;
    struct ext2_super_block super = {0};
    struct ext2_group_desc group = {0}; 
    struct ext2_inode inode = {0};
    struct ext2_dir_entry_2 dir = {0};
    struct ext2_dir_entry_2* dir_ptr = {0}; 
    
    fd = OpenDevice(fd, device);
	ReadSuperBlock(&super, fd);
	if (super.s_magic != EXT2_SUPER_MAGIC)
    {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(FAIL);
	}
    	
    ReadGroupDesc(&group, fd, block_size);
	ReadInode(fd, ROOT_INODE, &group, &inode);
	
	lseek(fd, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
    read(fd, &dir, block_size);
    printf("\n%s\n", filename);
	
	dir_ptr = &dir;
	
    while((size < (&inode)->i_size) && dir_ptr->inode)
    {
        char file_name[EXT2_NAME_LEN+1] = {0};
        memcpy(file_name, dir_ptr->name, dir_ptr->name_len);
        file_name[dir_ptr->name_len] = '\0';
        printf("\nname len: %u file name:%s dir_len:%u inode:%u\n", dir_ptr->name_len, file_name, dir_ptr->rec_len, dir_ptr->inode);
        if (0 == strcmp(file_name, filename))
        {
            break;
        }
        dir_ptr = (void*) dir_ptr + dir_ptr->rec_len;
        size += dir_ptr->rec_len;
    }
    
    ReadInode(fd, dir_ptr->inode, &group, &inode);
/*	lseek(fd, BLOCK_OFFSET(group->bg_inode_table) +
    (inode_num - 1) * sizeof(struct ext2_inode), SEEK_SET);*/
    lseek(fd, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
    read(fd, buffer, block_size);
    printf("%s\n", buffer);
    

	close(fd);
	return SUCCESS;
}
