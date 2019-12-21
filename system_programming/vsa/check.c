#include <stdio.h>
#include <stdlib.h>

#define TWOS_COMPLEMENT(x) (~(x) + 1)

int main()
{
    long num = 2147483648;
    
    typedef struct BlockHeader
    {
        long block_size;
        
        #ifndef NDEBUG
        long magic_num;
        #endif
    }header_t;
    
    header_t header = {9223372036854775807, 9};
    
    printf("size of blockheader %ld\n", sizeof(struct BlockHeader));
    
    printf("after 2s comp: %ld\n", TWOS_COMPLEMENT(header.block_size));
    
    printf("%ld\n", sizeof(long));
    printf("%lu\n", 0xFFFFFFFFFFFFFFFFUL);
    
    printf("%ld\n", TWOS_COMPLEMENT(num));   
        
    return 0;
}
