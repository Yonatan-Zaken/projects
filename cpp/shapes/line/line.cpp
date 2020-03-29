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
Shape(center, angle), Draw(color), m_length(length)
{
}

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
    double x1 = GetPosition().GetX() - (m_length / 2) * cos(GetAngle() * (PI / 180));
    double y1 = GetPosition().GetY() + (m_length / 2) * sin(GetAngle() * (PI / 180));
    double x2 = GetPosition().GetX() + (m_length / 2) * cos(GetAngle() * (PI / 180));
    double y2 = GetPosition().GetY() - (m_length / 2) * sin(GetAngle() * (PI / 180));
    
    DrawPolygon(GetColor(), 2, (int)x1, (int)y1, (int)x2, (int)y2);
}

} // namespace ilrd
