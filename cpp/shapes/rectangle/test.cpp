#include <iostream> // cout

#include "glut_utils.h"
#include "rectangle.hpp"

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
    Point p0(500, 500);
    Rectangle r1(p0, 0, COLOR_MAGENTA,300, 200);
    r1.SetWidth(50);
    r1.SetHeight(40);
    
}

int main(int argc, char *argv[])
{
    DrawInit(argc, argv, 1200, 1200, Test); 
    DrawMainLoop(); 
    return 0;
}
