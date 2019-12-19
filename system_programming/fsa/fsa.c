/*********************************/
/*   			             	 */
/*   System Programming          */
/*   FSA                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 19/12/19       */
/*   Reviewed by: shye           */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <assert.h> /*assert */

#include "fsa.h" /* fixed sized allocator functions */ 

#define WORD_IN_BYTES sizeof(size_t)
#define ALIGNMENT_FACTOR 7  
#define SIZE_OF_BLOCKHEADER sizeof(block_header_t)
#define SIZE_OF_FSA sizeof(fsa_t)

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

static size_t BlockSize(const size_t block_size)
{
    size_t total = block_size;
    
    while (0 != (total % WORD_IN_BYTES))
    {
        ++total;
    }
    
    return total;
}

static char *AlignAddress(void *allocated)
{
    byte_t runner = allocated;
    while (0 != (size_t)runner % WORD_IN_BYTES)
    {
        ++runner;
    }
    
    return runner;
}

fsa_t *FSAInit(void *allocated, const size_t segment_size, const size_t block_size)
{
    block_header_t *header = NULL;
    fsa_t *new_fsa = NULL;
    byte_t runner = NULL;
    size_t address_holder = 0;
    
    assert(NULL != allocated);
    
    new_fsa = allocated;
    new_fsa->block_size = BlockSize(block_size);
    new_fsa->segment_size = segment_size;
    
    runner = AlignAddress(allocated);

    new_fsa = (fsa_t *)runner;
    header = (block_header_t *)new_fsa;
    new_fsa->next_available_index = SIZE_OF_FSA + SIZE_OF_BLOCKHEADER;
    
    address_holder =  new_fsa->next_available_index;
    header += SIZE_OF_FSA / SIZE_OF_BLOCKHEADER;

    while (address_holder < 
          (segment_size - (new_fsa->block_size + SIZE_OF_BLOCKHEADER)))
    {
        address_holder += new_fsa->block_size + SIZE_OF_BLOCKHEADER;
        header->next_free_index = address_holder;
        header += (new_fsa->block_size + SIZE_OF_BLOCKHEADER) / 
                                           SIZE_OF_BLOCKHEADER;   
    }
    
    header->next_free_index = 0UL;
    return new_fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
    block_header_t *runner = NULL;
    size_t temp_next_available = 0UL;
    
    assert(NULL != fsa);
    
    if (0 == fsa->next_available_index)
    {
        return NULL;
    }
    runner = (block_header_t *)fsa + 
    (fsa->next_available_index - SIZE_OF_BLOCKHEADER) /
                                   SIZE_OF_BLOCKHEADER;
    
    temp_next_available = fsa->next_available_index;
    fsa->next_available_index = ((block_header_t *)runner)->next_free_index;
    runner->next_free_index = temp_next_available; 
   
    return ((byte_t)fsa + temp_next_available);
}

void FSAFree(void *block)
{
    block_header_t *header = NULL;
    size_t swap_index1 = 0UL;
    size_t swap_index2 = 0UL;
    fsa_t *fsa_free = NULL;
    
    assert(NULL != block);
    
    header = (block_header_t *)block;
    --header; 
    
    swap_index1 = header->next_free_index;
    
    header -= ((swap_index1 - SIZE_OF_BLOCKHEADER) /SIZE_OF_BLOCKHEADER); 
    fsa_free = (fsa_t *)header;
    
    swap_index2 = fsa_free->next_available_index;
   
    fsa_free->next_available_index = swap_index1;
    header += ((swap_index1 - SIZE_OF_BLOCKHEADER) / SIZE_OF_BLOCKHEADER); 
    header->next_free_index = swap_index2; 
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

size_t FSASuggestSize(const size_t blocks_count, const size_t block_size)
{
    return (BlockSize(block_size) + SIZE_OF_BLOCKHEADER) * blocks_count +
                                          SIZE_OF_FSA + ALIGNMENT_FACTOR; 
}
