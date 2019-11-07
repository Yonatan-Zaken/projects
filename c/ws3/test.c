#include <stdio.h>

int main()
{
    char *arr[4] = {"abcd","efg","hijkl","mnopq"};
    char **buffer = arr;   
    printf("array: %c\n", *arr[0]+2);
    
    return 0;
}
