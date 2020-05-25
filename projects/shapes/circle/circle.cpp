/*******************************
    Shapes - Circle
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include <cmath> // sin()

#include "glut_utils.h" // DrawCircle
#include "circle.hpp"

namespace ilrd
{

Circle::Circle(const Point& center, COLORS color, double radius): 
Shape(center), 
Draw(color), 
m_radius(radius)
{}

void Circle::SetRadius(double radius)
{
    m_radius = radius;
}

double Circle::GetRadius() const
{
    return m_radius;    
}

void Circle::Drawing() const
{
    DrawCircle(GetColor(), GetPosition().GetX(), GetPosition().GetY(), GetRadius());
}

} // namespace ilrd
