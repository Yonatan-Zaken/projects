/*******************************
    Shapes - Square
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include <cmath> // sin()

#include "glut_utils.h" // DrawPolygon
#include "square.hpp"

namespace ilrd
{

Square::Square(Point center, double angle, COLORS color, double length): 
Shape(center, angle), Draw(color), m_length(length)
{
}

double Square::GetLength() const
{
    return m_length;
}

void Square::SetLength(double length)
{
    m_length = length;
}

void Square::Drawing() const
{
    
}

} // namespace ilrd
