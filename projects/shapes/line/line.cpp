/*******************************
    Shapes - Line
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include <cmath> // sin()

#include "glut_utils.h" // DrawPolygon
#include "line.hpp"

namespace ilrd
{

Line::Line(Point center, double angle, COLORS color, double length): 
Shape(center, angle), 
Draw(color), 
m_length(length)
{}

void Line::SetLength(double length)
{
    m_length = length;
}

double Line::GetLength() const
{
    return m_length;
}

void Line::Drawing() const
{
    double convert_to_rad = PI / 180;
    double half_length = m_length / 2;
    double x = GetPosition().GetX();
    double y = GetPosition().GetY();
    double angle = GetAngle();
    
    double x1 = x - half_length * cos(angle * convert_to_rad);
    double y1 = y + half_length * sin(angle * convert_to_rad);
    double x2 = x + half_length * cos(angle * convert_to_rad);
    double y2 = y - half_length * sin(angle * convert_to_rad);
    
    DrawPolygon(GetColor(), 2, (int)x1, (int)y1, (int)x2, (int)y2);
}

} // namespace ilrd
