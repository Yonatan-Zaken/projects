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

typedef vsa_t block_header_t;
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
    RUN_TEST(952 == VSALargestChunkSize(vsa), "largest size");
    
    free(alloc);
}

static void VSATestAlloc()
{
    vsa_t *vsa = NULL;
    block_header_t *header = NULL;
    void *alloc = (void *)malloc(1000);
    void *ptr = NULL;
    void *hold_address = NULL;
    
    vsa = VSAInit(alloc, 1000);    
    header = vsa;
    
    ptr = VSAAlloc(vsa, 200);
    ptr = (block_header_t *)((char *)ptr - sizeof(struct BlockHeader));
    printf("%ld\n", ((block_header_t *)(ptr))->block_size);
    RUN_TEST(-200 == ((block_header_t *)(ptr))->block_size, "block size");
    ptr = (block_header_t *)((char *)ptr + sizeof(struct BlockHeader) + 200);
    printf("%ld\n", ((block_header_t *)(ptr))->block_size);
    RUN_TEST(752 == ((block_header_t *)(ptr))->block_size, "block size");
    printf("%ld\n", VSALargestChunkSize(vsa));
    RUN_TEST(736 == VSALargestChunkSize(vsa), "largest size");  
    
    ptr = VSAAlloc(vsa, 500);
    hold_address = ptr;
    ptr = (block_header_t *)((char *)ptr - sizeof(struct BlockHeader));
    printf("%ld\n", ((block_header_t *)(ptr))->block_size);
    RUN_TEST(-500 == ((block_header_t *)(ptr))->block_size, "block size");
    ptr = (block_header_t *)((char *)ptr + sizeof(struct BlockHeader) + 500);
    printf("%ld\n", ((block_header_t *)(ptr))->block_size);
    RUN_TEST(236 == ((block_header_t *)(ptr))->block_size, "block size");
    printf("%ld\n", VSALargestChunkSize(vsa));
    RUN_TEST(220 == VSALargestChunkSize(vsa), "largest size");
    
    VSAFree(hold_address);
    hold_address = (char*)hold_address - sizeof(struct BlockHeader);
    printf("%ld\n", ((block_header_t *)hold_address)->block_size);
    RUN_TEST(500 == ((block_header_t *)hold_address)->block_size, "block size");
    
    RUN_TEST(736 == VSALargestChunkSize(vsa), "largest size");
    
    
    free(alloc);
}

int main()
{
    VSATestInit();
    VSATestLargestSize();
    VSATestAlloc();
    
    return 0;
}
