/*******************************
    Shapes - Circle
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_CIRCLE_HPP
#define ILRD_RD8081_CIRCLEe_HPP

#include "draw.hpp"
#include "shapes.hpp"

namespace ilrd
{

class Circle : public Shape, public Draw
{

public:
    explicit Circle();
    explicit Circle(const Point& center, COLORS color, double radius);
    //~Circle() = default;
    //Circle(const Point&) = default;
    //Circle& operator=(const Point&) = default;
    
    void SetRadius(double length);
    double GetRadius() const;
    virtual void Drawing() const;
    
private:
    double m_radius;
};

std::ostream& operator<<(std::ostream& os, const Circle& circle)
{
    os << "Circle ";
    os << circle.GetPosition();
    os << circle.GetColor();
    os << circle.GetRadius();
    
    return os;
}


} //namespae ilrd

#endif // CIRCLE
