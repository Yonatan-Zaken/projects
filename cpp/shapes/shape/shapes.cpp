/*******************************
    Shapes 
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "shapes.hpp"

namespace ilrd
{

Shape::Shape(Point center, double angle):
m_center_position(center), m_angle(angle)
{
}

Shape::~Shape()
{
}

void Shape::Revolve(const Point& pivot, double angle)
{
    m_center_position.Revolve(pivot, angle);
}

void Shape::Rotate(double angle)
{
    m_angle += angle;
}

Point Shape::GetPosition() const
{
    return m_center_position;
}

void Shape::SetPosition(const Point& other)
{
    m_center_position = other;
}

double Shape::GetAngle() const
{
    return m_angle;
}

void Shape::SetAngle(double new_angle)
{
    m_angle = new_angle;
}

} // namespace ilrd
