/*********************************/
/*   			             	 */
/*   System Programming          */
/*   VSA                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 22/12/19       */
/*   Reviewed by: Daniel         */   
/*			                   	 */
/*********************************/

#include <assert.h> /* assert */

#include "vsa.h" 

#define SIZE_OF_VSA sizeof(vsa_t)
#define SIZE_OF_BLOCKHEADER sizeof(block_header_t) 
#define END_OF_SEGMENT 0x1000000000000000
#define DEADBEEF 0xDEADBEEF

struct BlockHeader
{
    long block_size;
    
    #ifndef NDEBUG
    long magic_num;
    #endif
};

typedef vsa_t block_header_t;
typedef char* byte_t;

static long Abs(long block_size)
{
    if (0 > block_size)
    {
        return -block_size;
    }
    
    else return block_size;
}

vsa_t *VSAInit(void *allocated, size_t segment_size)
{
    vsa_t *first_header = NULL;
    
    assert(NULL != allocated);
    
    first_header = allocated;
    
    #ifndef NDEBUG
    first_header->magic_num = DEADBEEF; 
    #endif
    
    first_header->block_size = segment_size - SIZE_OF_VSA - SIZE_OF_BLOCKHEADER;
    
    first_header = (block_header_t *)((byte_t)first_header + 
                    first_header->block_size + SIZE_OF_BLOCKHEADER);
    
    first_header->block_size = END_OF_SEGMENT;
    first_header = allocated;
    
    return first_header;
}


static vsa_t *FusionFunction(vsa_t *vsa)
{
    block_header_t *header_runner = vsa;
    block_header_t *header_base = vsa;
    block_header_t *address_holder = NULL;
    long free_memory_holder = 0;
    
    while (END_OF_SEGMENT != header_runner->block_size)
    {
        header_base = header_runner;
        
        while (0 <= header_runner->block_size && END_OF_SEGMENT != 
                                 header_runner->block_size)
        {
            free_memory_holder += header_runner->block_size + SIZE_OF_BLOCKHEADER;
            header_runner = (block_header_t *)((byte_t)header_runner + 
                     header_runner->block_size + SIZE_OF_BLOCKHEADER);
        }
        
        if (0 != free_memory_holder)
        {
            header_base->block_size = free_memory_holder - SIZE_OF_BLOCKHEADER;
        }
        
        while (0 > header_runner->block_size && (END_OF_SEGMENT != 
                                       header_runner->block_size))
        {
            header_runner = (block_header_t *)((byte_t)header_runner - 
                                    header_runner->block_size +
                                   SIZE_OF_BLOCKHEADER); 
        }
                                                           
    }
    
    return vsa;
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
    block_header_t *header = NULL;
    block_header_t *address_holder = NULL;
    size_t size_holder = 0;

    assert(NULL != vsa);  
    
    header = FusionFunction(vsa);
    
    while ((long)block_size >= (header->block_size + (long)SIZE_OF_BLOCKHEADER))
    {
        
        header = (block_header_t *)((byte_t)header + Abs(header->block_size)+ 
                                                        SIZE_OF_BLOCKHEADER);
    }    
    
    if (END_OF_SEGMENT == header->block_size)
    {
        return NULL;
    }
    else 
    {
        address_holder = (block_header_t *)((byte_t)header + SIZE_OF_BLOCKHEADER);
        size_holder = header->block_size;
        header->block_size = -block_size ;
        #ifndef NDEBUG
        header->magic_num = DEADBEEF;    
        #endif
        header = (block_header_t *)((byte_t)header + block_size +
                                            SIZE_OF_BLOCKHEADER);
        header->block_size = size_holder - block_size - SIZE_OF_BLOCKHEADER;      
    }
    return ((void *)address_holder);
}

size_t VSALargestChunkSize(vsa_t *vsa)
{
    block_header_t *header = NULL;
    long largest_size = 0;
    
    assert(NULL != vsa);
    
    header = FusionFunction(vsa);
    
    while (END_OF_SEGMENT != header->block_size)
    {
        if (largest_size < header->block_size)
        {
            largest_size = header->block_size;
        }
        header = (block_header_t *)((byte_t)header + Abs(header->block_size) +
                                                        SIZE_OF_BLOCKHEADER);
    }
    
    if (largest_size < (long)SIZE_OF_BLOCKHEADER)
    {
        return 0;
    }
    
    return (largest_size - (long)SIZE_OF_BLOCKHEADER);
}

void VSAFree(void *block)
{
    block_header_t *header = NULL;
    
    assert(NULL != block);

    header = block;
    --header;    
    assert(DEADBEEF == header->magic_num);
    
    if (0 > header->block_size)
    {
        header->block_size = -(header->block_size);
    }
}
