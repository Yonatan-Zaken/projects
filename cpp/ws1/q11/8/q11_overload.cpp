#include <stdio.h>
#include "overload.hpp"

int Foo(int a, int b)
{
    return a+b;
}

void Foo(char c)
{
    printf("%c\n", c);
}

void Foo(float f)
{
    printf("%f\n", f);
}

void Bar(char c)
{
    printf("char is : %c\n", c);
}
