/*******************************
    Shapes - Circle
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "circle.hpp"

namespace ilrd
{

Circle::Circle(double radius, double angle, Point center): 
Shape(center, angle), m_radius(radius)
{
}

Shape& Circle::Revolve(const Point& pivot, double angle)
{
    
}

void Circle::SetPosition(const Point& other)
{
    
}

} // namespace ilrd
