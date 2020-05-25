/*******************************
    Shapes 
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "shapes.hpp"

namespace ilrd
{

Shape::Shape(const Point& center, double angle):
m_center_position(center),
m_angle(angle)
{}

Shape::~Shape() noexcept
{}

void Shape::Revolve(const Point& pivot, double angle) 
{
    m_center_position.Revolve(pivot, angle);
}

void Shape::Rotate(double angle) noexcept
{
    m_angle += angle;
}

Point Shape::GetPosition() const noexcept
{
    return m_center_position;
}

void Shape::SetPosition(const Point& other) noexcept
{
    m_center_position = other;
}

double Shape::GetAngle() const noexcept
{
    return m_angle;
}

void Shape::SetAngle(double new_angle) noexcept
{
    m_angle = new_angle;
}

} // namespace ilrd
