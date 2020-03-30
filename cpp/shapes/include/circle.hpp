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
    explicit Circle(Point center, double angle, COLORS color, double radius);
    //~Circle() = default;
    //Circle(const Point&) = default;
    //Circle& operator=(const Point&) = default;
    
    void SetRadius(double length);
    double GetRadius() const;
    void Drawing() const;
    
private:
    double m_radius;
};

} //namespae ilrd

#endif // CIRCLE
