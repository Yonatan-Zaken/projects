#include <iostream> // cout

#include "circle.hpp"

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
    Point p0(400, 600);
    Point p1(400, 400);
    Circle c1(p1, 0, COLOR_YELLOW, 50);
    c1.Drawing();
    c1.Revolve(p0, 90);
    c1.Drawing();
    
}

int main(int argc, char *argv[])
{
    DrawInit(argc, argv, 1200, 1200, Test); 
    DrawMainLoop(); 
    return 0;
}
