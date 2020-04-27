#include <stdlib.h>
#include <stdio.h>

void *aligned_malloc(size_t bytes, size_t alignment)
{
    size_t address = 0;
    void *ptr1 = NULL;
    void *ptr2 = NULL;

    ptr2 = malloc(bytes + alignment + sizeof(size_t));
    if(NULL == ptr2)
    {
        return NULL;
    }

    address = (size_t)ptr2 + alignment + sizeof(size_t);
    ptr1 = (void *)(address - (address % alignment));
    *((size_t *)ptr1 - 1) = (size_t)ptr2;

    return ptr1;

}

void aligned_free(void *ptr)
{
    free((void *)(*((size_t *)ptr - 1)));
}

int main(int argc, char const *argv[])
{
    void *ptr = aligned_malloc(30, 16);
    void *ptr2 = aligned_malloc(43, 32);
    printf("%s\n", (0 == ((size_t)ptr % 16)) ? "aligned: 16" : "not aligned");
    printf("%s\n", (0 == ((size_t)ptr2 % 32)) ? "aligned: 32" : "not aligned");
    
    aligned_free(ptr); ptr = NULL;
    aligned_free(ptr2); ptr2 = NULL;

    return 0;
}
