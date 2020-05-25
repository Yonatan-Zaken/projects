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

Square::Square()
{
}

Square::Square(Point center, double angle, COLORS color, double length): 
Shape(center, angle), 
Draw(color), 
m_length(length)
{}

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
    double x = GetPosition().GetX();
    double y = GetPosition().GetY();
    double angle = GetAngle();
    double convert_to_rad = PI / 180;
    double half_length = GetLength() / 2;
    double cos_angle = cos(angle * convert_to_rad);
    double sin_angle = sin(angle * convert_to_rad);
    
    double x1 = x - half_length * cos_angle - half_length * sin_angle;
    double y1 = y - half_length * sin_angle + half_length * cos_angle;
    
    double x2 = x + half_length * cos_angle - half_length * sin_angle;
    double y2 = y + half_length * sin_angle + half_length * cos_angle;
    
    double x3 = x + half_length * cos_angle + half_length * sin_angle;
    double y3 = y + half_length * sin_angle - half_length * cos_angle;
    
    double x4 = x - half_length * cos_angle + half_length * sin_angle;
    double y4 = y - half_length * sin_angle - half_length * cos_angle;
    
    DrawPolygon(GetColor(), 4, (int)x1, (int)y1, (int)x2, (int)y2, (int)x3, (int)y3, 
    (int)x4, (int)y4);    
}

} // namespace ilrd
