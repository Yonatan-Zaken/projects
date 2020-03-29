/*******************************
    Shapes - Circle
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_CIRCLE_HPP
#define ILRD_RD8081_CIRCLE_HPP

#include <iosfwd>
#include "Circles.hpp"

namespace ilrd
{

class Circle : public Shape
{

public:
    Circle(double radius, double angle, Point center);
    //virtual ~Circle();
    //Circle(const Point&) = default;
    //Circle& operator=(const Point&) = default;
    
    virtual Circle& Revolve(const Point& pivot, double angle) =0;
//    virtual const Point& GetPosition() const;
    virtual void SetPosition(const Point& other) =0;
//    virtual const double& GetAngle() const;
//    virtual void SetAngle(double new_angle);
    
private:
    m_double radius;
};

} //namespae ilrd

#endif // CIRCLE
