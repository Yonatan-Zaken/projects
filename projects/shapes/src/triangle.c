#include <stdio.h>
#include <mcheck.h>

#include "glut_utils.h"
#include "point.hpp"


int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 10 ;

static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();

int main(int argc, char** argv)
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);
    
    DrawMainLoop();

    printf("exit\n");

    return 0;
}


static void DrawFunction()
{
    /* printf("Drawing\n"); */

    /* draw rectangle */
    DrawPolygon(COLOR_MAGENTA, 3, (int)400, (int)400, (int)0, (int)600, (int)200, (int)400, (int)0, (int)400);

    if (drawCircle)
        DrawCircle(COLOR_GREEN, xCircle, yCircle, rCircle);
        
    DrawPolygon(COLOR_RED, 1, (int)300, (int)200);
}


static int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
        rCircle *= 1.1;
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        rCircle *= 0.9;
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
        return 1;
    }

    return 0;
}


static int MotionFunction(int x, int y)
{
    printf("Mouse: %d,%d\n", x, y);

    return 0;
}


static int TimerFunction()
{
    xCircle += 0;
    yCircle += 1;

    return 1;  /* draw */
}
