#include <stdio.h>

int main()
{
    
    float y;
    long l;
    
    union point{
        int c;
        double a;
    };
    
    union point first_point;
    
    first_point.c = 10;
    first_point.a = 20; 
    
    printf("%d\n\n", sizeof(first_point));
    
    
    return 0;
}
