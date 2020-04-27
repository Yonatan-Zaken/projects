#include <stdio.h>
#include <stdlib.h>

#define ALIGNED_MALLOC(SIZE_TO_ALIGN, POWER_OF_TWO)\
(SIZE_TO_ALIGN + (POWER_OF_TWO - 1)) & ~(POWER_OF_TWO - 1)

void *aligned_malloc(size_t bytes, size_t alignment)
{
    void *ptr1 = NULL;
    void *ptr2 = NULL;
    size_t address = 0;

    ptr1 = malloc(bytes + (alignment - 1) + sizeof(size_t));
    
    address = ALIGNED_MALLOC((size_t)ptr1 + (alignment - 1) + 
    sizeof(size_t), alignment);

    ptr2 = (void *)address;
    *((size_t *)ptr2 - 1) = (size_t)ptr1;
    
    return ptr2;
}

void aligned_free(void *ptr)
{
    free((void *)(*((size_t *)ptr - 1)));
}   

int main(int argc, char const *argv[])
{
    void *ptr1 = aligned_malloc(7, 16);
    void *ptr2 = aligned_malloc(23, 32);
    printf("%s\n", (0 == ((size_t)ptr1 % 16)) ? "aligned: 16" : "not aligned");
    printf("%s\n", (0 == ((size_t)ptr2 % 32)) ? "aligned: 32" : "not aligned");
    
    aligned_free(ptr1);
    aligned_free(ptr2);

    return 0;
}
