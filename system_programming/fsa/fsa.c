/*********************************/
/*   			             	 */
/*   System Programming          */
/*   FSA                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 19/12/19       */
/*   Reviewed by: shye           */   
/*			                   	 */
/*********************************/

#include <assert.h> /*assert */

#include "fsa.h" 

#define WORD_IN_BYTES sizeof(size_t)
#define SIZE_OF_BLOCKHEADER sizeof(block_header_t)
#define SIZE_OF_FSA sizeof(fsa_t)

#define ALIGNMENT_FACTOR (WORD_IN_BYTES - 1)  
#define ALIGN_SIZE(SizeToAlign, PowerOfTwo)\
        (((SizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))

typedef char* byte_t;

struct FixedSizeAllocator
{
    size_t segment_size;
    size_t next_available_index;
    size_t block_size;
};

typedef struct BlockHeader
{
    size_t next_free_index;
} block_header_t;

static size_t BlockSize(size_t block_size)
{
    return ALIGN_SIZE(block_size, sizeof(size_t));
}

static void *AlignAddress(void *allocated)
{
    return ((void*)ALIGN_SIZE((size_t)allocated, sizeof(size_t)));
}

fsa_t *FSAInit(void *allocated, size_t segment_size, size_t block_size)
{
    fsa_t *new_fsa = NULL;
    block_header_t *header = NULL;    
    size_t next_free_holder = 0;
    
    assert(NULL != allocated);
    
    new_fsa = AlignAddress(allocated);
    new_fsa->block_size = BlockSize(block_size);
    new_fsa->segment_size = segment_size;
    new_fsa->next_available_index = SIZE_OF_FSA + SIZE_OF_BLOCKHEADER;
    
    next_free_holder =  new_fsa->next_available_index;
    header = (block_header_t *)((byte_t)new_fsa + SIZE_OF_FSA);
    
    while (next_free_holder < 
          (segment_size - (new_fsa->block_size + SIZE_OF_BLOCKHEADER)))
    {
        next_free_holder += new_fsa->block_size + SIZE_OF_BLOCKHEADER;
        header->next_free_index = next_free_holder;
        header = (block_header_t *)((byte_t)header + new_fsa->block_size + 
                                                     SIZE_OF_BLOCKHEADER);            
    }
    
    header->next_free_index = 0UL;
    return new_fsa;
}

static void Swap(fsa_t *fsa, block_header_t *header)
{
    size_t temp_next_available = fsa->next_available_index;
    fsa->next_available_index = header->next_free_index;
    header->next_free_index = temp_next_available;
}

void *FSAAlloc(fsa_t *fsa)
{
    block_header_t *header = NULL;
    
    assert(NULL != fsa);
    
    if (0 == fsa->next_available_index)
    {
        return NULL;
    }
    
    header = (block_header_t *)((byte_t)fsa + fsa->next_available_index - 
                                                    SIZE_OF_BLOCKHEADER);
    Swap(fsa, header);
    
    return ((byte_t)header + SIZE_OF_BLOCKHEADER);
}

void FSAFree(void *block)
{
    fsa_t *fsa_free = NULL;
    block_header_t *header = NULL;
  
    assert(NULL != block);
    
    header = (block_header_t *)((byte_t)block - SIZE_OF_BLOCKHEADER);
    fsa_free = (fsa_t *)((byte_t)header - header->next_free_index +
                                              SIZE_OF_BLOCKHEADER);   
    Swap(fsa_free, header);
}

size_t FSACountFree(const fsa_t *fsa)
{
    const char *runner = NULL;
    size_t header_value = 0UL;
    size_t counter = 0UL;
    
    assert(NULL != fsa);
    
    header_value = fsa->next_available_index; 
    runner = (byte_t)fsa;
    
    while (0 != header_value)
    {
        runner += header_value - SIZE_OF_BLOCKHEADER;
        header_value = ((block_header_t *)runner)->next_free_index;
        ++counter;
        runner = (byte_t)fsa;
    }
    
    return counter;
}

size_t FSASuggestSize(size_t blocks_count, size_t block_size)
{
    return (BlockSize(block_size) + SIZE_OF_BLOCKHEADER) * blocks_count +
                                          SIZE_OF_FSA + ALIGNMENT_FACTOR; 
}
