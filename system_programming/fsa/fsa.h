#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /*size_t*/

typedef struct FixedSizeAllocator fsa_t;

/*
* FSAInit() - 
* Returns pointer to the fsa_t. 
* complexity of O(1);
*/
fsa_t *FSAInit(void *allocated, size_t segment_size, size_t block_size);

/*
* FSAAlloc() -
* Allocate memory block to the user.
* returns pointer to the block.
* complexity of O(1);                  
*/
void *FSAAlloc(fsa_t *fsa);

/*
* FSAFree()-
* Gets pointer to memory block and free it.
* Returns void.
* complexity of O(1).               
*/
void FSAFree(void *block);

/*
* FSACountFree()-
* Counts the number of free blocks in the segment.
* complexity of O(n)
*/
size_t FSACountFree(const fsa_t *fsa);

/*
* FSASuggestSize() - 
* Gets number of blocks demanded by the user and returns the segment size suggested.
* complexity of O(1);              
*/
size_t FSASuggestSize(size_t blocks_count, size_t block_size);

#endif
