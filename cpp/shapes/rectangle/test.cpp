#include <iostream> // cout

#include "line.hpp"

using namespace ilrd;

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

static void Test()
{
    Point p1;
    Point p2(0, -5);
    Line l1(4, 0, p2);
    l1.Rotate(45);
    l1.Revolve(p1, 90);
    
}

int main()
{
    Test();
    return 0;
}
