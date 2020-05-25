#include <iostream> // cout

#include "line.hpp"

#define PI 3.1415927

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
    Point p1(500, 1000);
    Point p2(500, 500);
    Line l1(p2, 0, COLOR_RED, 300);
    l1.Drawing();
    l1.Rotate(45);
    l1.Drawing();
    l1.Revolve(p1, 90);
    l1.Drawing(); 

}

int main(int argc, char *argv[])
{
    DrawInit(argc, argv, 1200, 1200, Test); 
    DrawMainLoop();  
    return 0;
}
