#include <stdio.h>


void Shift(char *str, size_t size, size_t n)
{
    size_t i = 0;
    size_t current_idx = 0;
    char char_holder = str[0];
    char next = 0;
    
    for (i = 0; i < size; ++i)
    {
        current_idx = (current_idx + n) % size;
        next = str[current_idx];
        str[current_idx] = char_holder;
        char_holder = next;
    }
}


int main()
{
    char str[] = "hello";
    Shift(str, 5, 2);
    printf("%s\n", str);    
        
    return 0;
}
