/*******************************
    Shapes - Circle
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_CIRCLE_HPP
#define ILRD_RD8081_CIRCLEe_HPP

#include <boost/shared_ptr.hpp>
#include <sstream>
#include <iostream>

#include "draw.hpp"
#include "shapes.hpp"

namespace ilrd
{

class Circle : public Shape, public Draw
{

public:
    explicit Circle(const Point& center, COLORS color, double radius);
    //~Circle() = default;
    //Circle(const Point&) = default;
    //Circle& operator=(const Point&) = default;
    
    std::ostream& operator<<(std::ostream& os) const
    {
        os << typeid(Circle).name() << " ";
        os << GetPosition().GetX() << " ";
        os << GetPosition().GetY() << " ";
        os << GetColor() << " ";
        os << GetRadius() << " ";

        return os;
    }

    void SetRadius(double length);
    double GetRadius() const;
    virtual void Drawing() const;
    
private:
    double m_radius;
};

boost::shared_ptr<Circle> CreateCircle(std::istream& is)
{ 
    double x;
    double y;
    is >> x;
    is >> y;
    Point point(x, y);

    int color;
    is >> color;

    double radius;
    is >> radius;

    return boost::shared_ptr<Circle>(new Circle(point, (COLORS)color, radius));
}

} //namespae ilrd

#endif // CIRCLE
