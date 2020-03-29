/*******************************
    Shapes - Rectangle
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include <cmath> // sin()

#include "glut_utils.h" // DrawPolygon
#include "rectangle.hpp"

namespace ilrd
{

Rectangle::Rectangle(Point center, double angle, COLORS color, double width, double height): 
Shape(center, angle), Draw(color), m_width(width), m_height(height)
{
}

double Rectangle::GetWidth() const
{
    return m_width;
}

double Rectangle::GetHeight() const
{
    return m_height;
}

void Rectangle::SetWidth(double width)
{
    m_width = width;
}

void Rectangle::SetHeight(double height)
{
    m_height = height;
}

void Rectangle::Drawing() const
{
    
}

} // namespace ilrd
