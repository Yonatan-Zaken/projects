#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    /*
    char str1[] = "abcde";
    char *str2 = str1 + 2;
    size_t n = 3;
    
    printf("%ld\n", (size_t)(str1 + n));
    printf("%ld\n", (size_t)str2);
    */
    
    int n = 4660;
    int *p = &n;
    
    printf("%d\n", *((char*)p));
    
    
    return 0;
}
