#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char src[] = "$$";
    char dest[] = "abcde";
    
    strcpy(dest, src);
    
    printf("%s\n", dest); 
    
    return 0;
}
