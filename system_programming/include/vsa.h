#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /*size_t*/

typedef struct BlockHeader vsa_t;

/*
* VSAInit() -
* Gets pointer to the start of the memory space 
* Returns pointer to the vsa_t. 
* complexity of O(1);
*/
vsa_t *VSAInit(void *allocated, size_t segment_size);

/*
* VSAAlloc() -
* Allocate memory block to the user.
* returns pointer to the block.
* complexity of O(n);                  
*/
void *VSAAlloc(vsa_t *vsa, size_t block_size);

/*
* VSAFree()-
* Gets pointer to memory block and free it.
* complexity of O(1).               
*/
void VSAFree(void *block);

/*
* VSALargestChunkSize() - 
* Gets pointer to the start of the memory space
* Returns the largest available size in the memory space
* complexity of O(n);              
*/
size_t VSALargestChunkSize(vsa_t *vsa);

#endif
