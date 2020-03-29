/*******************************
    Shapes 
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "shapes.hpp"

namespace ilrd
{

Shape::Shape(Point center, double angle): m_center_position(center), m_angle(angle)
{
}

Shape::~Shape()
{
}

const Point& Shape::GetPosition() const
{
    return m_center_position;
}

const double& Shape::GetAngle() const
{
    return m_angle;
}

void Shape::SetAngle(double new_angle)
{
    m_angle = new_angle;
}

} // namespace ilrd
