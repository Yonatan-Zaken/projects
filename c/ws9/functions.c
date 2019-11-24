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
    
    char str1[] = "abcdefghi";
    char *str2 = str1 + 3;
    
    printf("%s\n", memmove(str2, str1, 5));
    
    
    
    return 0;
}


                         
