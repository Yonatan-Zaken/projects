/*************************
         EXT2
      Header File
    Author : RD8081
      Date : 05/04/2020          
*************************/
#ifndef ILRD_RD8081_EX2_H
#define ILRD_RD8081_EX2_H

int PrintSuperBlock(const char *device);

int PrintGroupDescriptors(const char *device);

int PrintFileContent(const char *device, const char *filename);

#endif /* ILRD_RD8081_EX2_HPP */

/* to include in .c file */

/*#include <ext2fs/ext2_fs.h>*/ /* ext2_super_block */
/*#include "ext2.h"*/

