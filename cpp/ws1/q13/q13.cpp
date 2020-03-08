#include <stdio.h>

const int j = 22;
int k = 33;

int main ()
{
    const int i = 3;
    int *ip = (int *)&i;
    *ip = 5;
    int arr[i];
    
    printf("%d %d\n", i, *ip);
    
    return 0;
}

