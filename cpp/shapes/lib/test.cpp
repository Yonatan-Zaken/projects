#include <stdio.h> // cout
#include <string.h>
#include <iostream>

#include "point.hpp"

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS %s\n", error_message);\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

using namespace ilrd;

static void CtorTest()
{
    Point p1;
    Point p2(4.2, 2.2);
    p2.Move(1, 1);
    Point p3(p2);
    RUN_TEST(p1 != p2, "!=");
    RUN_TEST(p3 == p2, "==");
    Point p5(5, 5);
    p1.Revolve(p5, 0.785398);
    std::cout << p1;
}


int main()
{
    CtorTest();

	return 0;
}
