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
Shape(center, angle), 
Draw(color), 
m_width(width), 
m_height(height)
{}

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
    double x = GetPosition().GetX();
    double y = GetPosition().GetY();
    double angle = GetAngle();
    double convert_to_rad = PI / 180;
    double half_width = GetWidth() / 2;
    double half_height = GetHeight() / 2;
    double cos_angle = cos(angle * convert_to_rad);
    double sin_angle = sin(angle * convert_to_rad);
    
    double x1 = x - half_width * cos_angle - half_height * sin_angle;
    double y1 = y - half_width * sin_angle + half_height * cos(angle * convert_to_rad);
    
    double x2 = x + half_width * cos_angle - half_height * sin_angle;
    double y2 = y + half_width * sin_angle + half_height * cos(angle * convert_to_rad);
    
    double x3 = x + half_width * cos_angle + half_height * sin_angle;
    double y3 = y + half_width * sin_angle - half_height * cos(angle * convert_to_rad);
    
    double x4 = x - half_width * cos_angle + half_height * sin_angle;
    double y4 = y - half_width * sin_angle - half_height * cos(angle * convert_to_rad);
    
    DrawPolygon(GetColor(), 4, (int)x1, (int)y1, (int)x2, (int)y2, (int)x3, (int)y3, 
    (int)x4, (int)y4);
}

} // namespace ilrd
