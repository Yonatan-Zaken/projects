#include <stdio.h>


int RecCharInArray(char *str, size_t size, char c)
{
    char result = 1;
    while ('\0' != *str)
    {
        result *= (c ^ *str);
        ++str;
    }
    
    return (0 == result);
}


int main()
{
    char str[] = "gxtpw";
    
    printf("%d\n", RecCharInArray(str, 5, 'q'));    
        
    return 0;
}
