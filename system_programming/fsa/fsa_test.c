#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "fsa.h"

#define UNUSED(x) (void)(x)

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

struct FixedSizeAllocator
{
    size_t segment_size;
    size_t next_available_index;
    size_t block_size;
};

struct BlockHeader
{
    size_t next_free_index;
};

static void FSATest1()
{
    fsa_t *new_fsa = NULL;
    
    struct BlockHeader block = {0};
    struct FixedSizeAllocator fsa = {0};
    
    void *ptr = NULL;
    size_t block_size = 13;
    size_t blocks_count = 3;
    size_t suggest = FSASuggestSize(blocks_count, block_size);
    void *alloc = (void *)malloc(suggest);
    
    printf("FSATest1:\n");
     
    RUN_TEST(103 == suggest, "suggeest test");
    
    new_fsa = FSAInit(alloc, suggest, block_size);
    
    RUN_TEST(3 == FSACountFree(new_fsa), "size count test");
    
    ptr = new_fsa;
    ptr = (char*)ptr + sizeof(struct FixedSizeAllocator);
    RUN_TEST(56 == *(size_t *)ptr, "header test");
      
    ptr = FSAAlloc(new_fsa);
    printf("address after alloc to block 1 %ld\n", (size_t)ptr);
    
    ptr = (char *)ptr - sizeof(struct BlockHeader);
    block.next_free_index = *(size_t *)ptr;    
    RUN_TEST(32 == block.next_free_index, "alloc test");
    
    ptr = FSAAlloc(new_fsa);
    printf("address after alloc to block 2 %ld\n", (size_t)ptr);
    
    ptr = (char *)ptr - sizeof(struct BlockHeader);
    block.next_free_index = *(size_t *)ptr;    
    RUN_TEST(56 == block.next_free_index, "alloc test");
    
    ptr = FSAAlloc(new_fsa);
    printf("address after alloc to block 3 %ld\n", (size_t)ptr);
    
    ptr = (char *)ptr - sizeof(struct BlockHeader);
    block.next_free_index = *(size_t *)ptr;    
    RUN_TEST(80 == block.next_free_index, "alloc test");
    
    RUN_TEST(0 == FSACountFree(new_fsa), "size count test");
    
    free(alloc);
    
}

static void FSATest2()
{
    fsa_t *new_fsa = NULL;
    
    struct BlockHeader block = {0};
    struct FixedSizeAllocator fsa = {0};
    
    void *ptr = NULL;
    size_t block_size = 21;
    size_t blocks_count = 6;
    size_t suggest = FSASuggestSize(blocks_count, block_size);
    void *alloc = (void *)malloc(suggest);

    printf("\nFSATest2:\n");
    
    new_fsa = FSAInit(alloc, suggest, block_size);

    RUN_TEST(223 == suggest, "suggeest test");    
    RUN_TEST(6 == FSACountFree(new_fsa), "size count test");
    
    ptr = FSAAlloc(new_fsa);
    RUN_TEST(5 == FSACountFree(new_fsa), "size count test");
    ptr = FSAAlloc(new_fsa);
    RUN_TEST(4 == FSACountFree(new_fsa), "size count test");
    ptr = FSAAlloc(new_fsa);    
    RUN_TEST(3 == FSACountFree(new_fsa), "size count test");
    ptr = FSAAlloc(new_fsa);    
    RUN_TEST(2 == FSACountFree(new_fsa), "size count test");
    
    FSAFree(ptr);
    RUN_TEST(3 == FSACountFree(new_fsa), "size count test");
    
    free(alloc);
}

int main()
{
    FSATest1();
    FSATest2();
    return 0;
}
