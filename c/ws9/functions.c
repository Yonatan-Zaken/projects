#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char str[20] = "helloworldhelloworld";
    int x = 'c';
    memset(str, 99, 26);
    printf("%s\n", str);
    
    printf("%d\n", x);
    
    return 0;
}
