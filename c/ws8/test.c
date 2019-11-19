#include <stdio.h>

int main()
{
    char *c;
    float y;
    long l;
    
    struct point{
        char *c;
        char ch;
    }first_point;
    
    printf("%d\n\n", sizeof());
    
    printf("char *c = %p\n", &c, &c+1);
    printf("%d\n", (int)(&first_point + 1) - (int)&first_point);
    
    return 0;
}
