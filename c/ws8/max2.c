#include <stdio.h>

#define MAX2(a, b) a > b ? a : b

#define MAX3(a, b, c) MAX2(MAX2(a, b), c) 

#define SIZEOF_VAR(x) (char*)(&x + 1) - (char*)(&x)

    

int main()
{
    char a[5] = {1,2,3,4,5};
    printf("%f\n", MAX2(-2.5,-12.265));
    printf("%d\n", MAX2(MAX2(18, 3), 6));   
    printf("%ld\n", SIZEOF_VAR(a));
    printf("%p %p %p\n", &a, &a+1, &a+2);   
    return 0;
}
