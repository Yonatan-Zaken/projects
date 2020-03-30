#include <iostream> // cout

#include "glut_utils.h"
#include "line.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "square.hpp"

using namespace ilrd;

static void TestLine()
{
    Point p1(300, 800);
    Line cross(p1, 0, COLOR_MAGENTA, 50);
    cross.Drawing();
    cross.Rotate(90);
    cross.Drawing();
    
    Point p2(300, 500);
    Line l1(p2, 0, COLOR_RED, 300);
    l1.Drawing();
    l1.Rotate(45);
    l1.Drawing();
    
    for (size_t i = 0; i < 11; ++i)
    {
        l1.Revolve(p1, 30 * (3.14 / 180) );
        l1.Drawing();    
    }
    
        
    l1.SetPosition(Point(800, 500));
    l1.Drawing();
    Point p3(800, 800); 
    Line l2(p3, 0, COLOR_BLUE, 200);
    l2.Drawing();
    l2.SetAngle(90);
    l2.Drawing();
    l2.Rotate(45);
    l2.Drawing();
    l2.Rotate(90);
    l2.Drawing();
    l2.SetAngle(315);
    l1.SetPosition(Point(300,300));
    l1.Drawing();
    l2.SetPosition(Point(300,300));
    l2.Drawing();
}

static void TestCircle()
{
    Point p0(400, 600);
    Circle c1(Point(400, 400), 0, COLOR_YELLOW, 50);
    c1.Drawing();
    c1.Revolve(p0, 90);
    c1.Drawing();
    c1.SetPosition(Point(900,300));
    c1.Drawing();
    c1.SetRadius(200);
    c1.Drawing();
    c1.SetRadius(100);
    c1.Drawing();
    c1.SetRadius(50);
    c1.Drawing();
    
    Point p1(500, 500);
    Line l1(p1, 0, COLOR_RED, 100);
    l1.Drawing();
    l1.Rotate(90);
    l1.Drawing();
    Line l2(Point(600,500), 0, COLOR_RED, 100);
    l2.Drawing();
    l2.Rotate(90);
    l2.Drawing();
    Circle c2(Point(600,500), 0, COLOR_GREEN, 30);
    c2.Drawing();
    c2.Revolve(p1, 20 * (3.145 / 180));
    c2.Drawing();
    c2.Revolve(p1, 20 * (3.145 / 180));
    c2.Drawing();
    c2.Revolve(p1, 20 * (3.145 / 180));
    c2.Drawing();
    c2.Revolve(p1, 20 * (3.145 / 180));
    c2.Drawing();
    c2.Revolve(p1, 20 * (3.145 / 180));
    c2.Drawing();
    c2.Revolve(p1, 20 * (3.145 / 180));
    c2.Drawing();
    c2.Revolve(p1, 20 * (3.145 / 180));
    c2.Drawing();
}

static void TestRectangle()
{
    Point p0(500, 500);
    Point p1(500, 900);
    Rectangle r1(p0, 0, COLOR_MAGENTA,300, 200);
    r1.Drawing();
    r1.Rotate(45);
    r1.Drawing();
    r1.Rotate(45);
    r1.Drawing();
    r1.Rotate(45);
    r1.Drawing();
    r1.SetAngle(0);
    r1.Revolve(p1, 90);
    r1.Drawing();
}

static void TestSquare()
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
    DrawInit(argc, argv, 1200, 1200, TestLine); 
    DrawMainLoop(); 
    
    DrawInit(argc, argv, 1200, 1200, TestSquare); 
    DrawMainLoop();
    
    DrawInit(argc, argv, 1200, 1200, TestCircle); 
    DrawMainLoop(); 
    
    DrawInit(argc, argv, 1200, 1200, TestRectangle); 
    DrawMainLoop();
    
    return 0;
}
