#include <stdio.h>

#define ASCII 256

int RecMult(int a, int b, int counter)
{
    int result = 0;
    if ((0 == b) || (0 == a))
    {
        return 0;
    }
    
    if (counter != (b - 1))
    {
        ++counter;
        result = RecMult(a, b, counter);
    }
    
    return (result += a);
}

int main()
{
    int a = 11, b = 3;
    int counter = 0;
    printf("%d\n", RecMult(a, b, counter));
    
    return 0;
}
