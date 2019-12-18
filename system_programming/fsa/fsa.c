/*********************************/
/*   			             	 */
/*   System Programming          */
/*   FSA                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 17/12/19       */
/*   Reviewed by: Israel         */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */
#include <assert.h> /*assert */

#include "fsa.h"

#define WORD_IN_BYTES sizeof(size_t)
#define ALIGNMENT_FACTOR 7  

struct FixedSizeAllocator
{
    size_t segment_size;
    size_t next_available_index;
    size_t block_size;
};

typedef struct BlockHeader
{
    size_t next_free_index;
}block_header_t;

size_t BlockSize(const size_t block_size)
{
    size_t total = block_size;
    
    while (0 != (total % WORD_IN_BYTES))
    {
        ++total;
    }
    
    return total;
}

fsa_t *FSAInit(void *allocated, const size_t segment_size, const size_t block_size)
{
    block_header_t *header = NULL;
    fsa_t *new_fsa = NULL;
    char *runner = NULL;
    size_t address_holder = 0;
    
    assert(NULL != allocated);
    
    new_fsa = allocated;
    new_fsa->block_size = BlockSize(block_size);
    new_fsa->segment_size = segment_size;
    
    runner = allocated;
    while (0 != (size_t)runner % WORD_IN_BYTES)
    {
        ++runner;
    }

    new_fsa = (fsa_t *)runner;
    header = (block_header_t *)new_fsa;
    new_fsa->next_available_index = sizeof(fsa_t) + sizeof(block_header_t);
    
    address_holder =  new_fsa->next_available_index;
    header += sizeof(fsa_t) / sizeof(block_header_t);

    printf("%ld\n", header); 
    
    while (address_holder < 
          (segment_size - (new_fsa->block_size + sizeof(block_header_t))))
    {
        address_holder += new_fsa->block_size + sizeof(block_header_t);
        header->next_free_index = address_holder;
        
        printf("%ld\n", header->next_free_index);
        
        header += (new_fsa->block_size + sizeof(block_header_t)) / 
                                           sizeof(block_header_t);
       
        printf("%ld\n", header);

    }
    
    header->next_free_index = 0UL;
    
    printf("%ld\n", header->next_free_index);
    
    printf("fsa address %ld\n", (size_t)new_fsa);
    return new_fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
    char *runner = NULL;
    size_t temp_next_av = 0;
    
    assert(NULL != fsa);
    
    if (0 == fsa->next_available_index)
    {
        return NULL;
    }
    printf("next_available_index%ld\n",fsa->next_available_index);
    
    runner = (char *)fsa + fsa->next_available_index - WORD_IN_BYTES;
    printf("runner%ld\n",*runner);
    temp_next_av = fsa->next_available_index;
    
    fsa->next_available_index = *runner;
    printf("next_available_index%ld\n",fsa->next_available_index);
    
    *runner = temp_next_av; 
    printf("next_free_index%ld\n\n",*runner);

    return ((char *)fsa + temp_next_av);
}

void FSAFree(void *block)
{
    block_header_t *header = NULL;
    size_t temp1 = 0;
    size_t temp2 = 0;
    char *runner = NULL;
    fsa_t *fsa_free = NULL;
    
    assert(NULL != block);
    
    printf("free:\n\n");
    header = (block_header_t *)block - 1; 
    printf("%ld\n", header);
 
    printf("next_free_index before%ld\n", header->next_free_index);
   
    temp1 = header->next_free_index;
    
    header -= ((temp1-1) / sizeof(block_header_t)); 
    fsa_free = (fsa_t *)header;
    printf("%ld\n", header);
    temp2 = fsa_free->next_available_index;
   
    fsa_free->next_available_index = temp1;
    header += ((temp1-1) / sizeof(block_header_t)); 
    header->next_free_index = temp2;
    printf("next_free_index after%ld\n", header->next_free_index);
    printf("%ld\n", header);
}

size_t FSACountFree(const fsa_t *fsa)
{
    const fsa_t *runner = NULL;
    size_t header_value = 0;
    size_t counter = 0;
    
    assert(NULL != fsa);
    
    header_value = fsa->next_available_index; 
    runner = fsa;
    
    while (0 != header_value)
    {
        runner += header_value;
        header_value = *(size_t *)runner;
        ++counter;
    }
    
    return counter;
}

size_t FSASuggestSize(const size_t blocks_count, const size_t block_size)
{
    return (BlockSize(block_size) + sizeof(block_header_t))
            * blocks_count + sizeof(fsa_t) + ALIGNMENT_FACTOR; 
}
