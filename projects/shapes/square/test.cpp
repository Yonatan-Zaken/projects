#include <iostream> // cout

#include "glut_utils.h"
#include "square.hpp"

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
    Point p1(500, 900);
    Square s1(p0, 0, COLOR_WHITE, 300);
    s1.Drawing();
    s1.Drawing();
    s1.Rotate(45);
    s1.Drawing();
    s1.Rotate(45);
    s1.Drawing();
    s1.Rotate(45);
    s1.Drawing();
    s1.SetAngle(0);
    s1.Revolve(p1, 45);
    s1.Drawing();
    s1.Revolve(p1, 45);
    s1.Drawing();
    s1.SetPosition(Point(900,300));
    s1.Drawing();
    s1.SetLength(200);
    s1.Drawing();
    s1.SetLength(100);
    s1.Drawing();
}

int main(int argc, char *argv[])
{
    DrawInit(argc, argv, 1200, 1200, Test); 
    DrawMainLoop(); 
    return 0;
}
