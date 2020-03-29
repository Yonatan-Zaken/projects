/*******************************
    Shapes - Rectangle
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "rectangle.hpp"

namespace ilrd
{

Rectangle::Rectangle(double width, double height, double angle, Point center): 
Shape(center, angle), m_width(width), m_height(height)
{
}

Shape& Rectangle::Revolve(const Point& pivot, double angle)
{
    
}

void Rectangle::SetPosition(const Point& other)
{
    
}

} // namespace ilrd
