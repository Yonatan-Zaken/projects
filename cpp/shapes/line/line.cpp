/*******************************
    Shapes - Line
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "line.hpp"

namespace ilrd
{

Line::Line(double length, double angle, Point center): 
Shape(center, angle), m_length(length)
{
}

Shape& Line::Rotate(double angle)
{
    Shape::SetAngle(angle);
    
    return *this;
}

Shape& Line::Revolve(const Point& pivot, double angle)
{
    
}

void Line::SetPosition(const Point& other)
{
    
}

} // namespace ilrd
