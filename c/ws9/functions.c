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
    
    int n = 4812;
    int temp = 0;
    char buffer[40]; 
    temp = n % 10;
    
    buffer[0] = temp + 48;
    
    printf("%c\n", buffer[0]);
    
    
    return 0;
}
