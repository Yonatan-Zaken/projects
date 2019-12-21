#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "vsa.h"

#define FREE(x) {free(x); x = NULL;}
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

struct BlockHeader
{
    long block_size;
    
    #ifndef NDEBUG
    long magic_num;
    #endif
};

static void VSATestInit()
{
    vsa_t *vsa = NULL;
    void *alloc = (void *)malloc(100);
    
    vsa = VSAInit(alloc, 100);
    
    RUN_TEST(68 == vsa->block_size, "block size");
    
    free(alloc);
}

static void VSATestLargestSize()
{
    vsa_t *vsa = NULL;
    void *alloc = (void *)malloc(1000);
    
    vsa = VSAInit(alloc, 1000);
    
    RUN_TEST(968 == vsa->block_size, "block size");
    RUN_TEST(968 == VSALargestChunkSize(vsa), "largest size");
    
    free(alloc);
}

int main()
{
    VSATestInit();
    VSATestLargestSize();
    
    return 0;
}
