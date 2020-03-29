/*******************************
    Shapes - Rectangle
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_RECTANGLE_HPP
#define ILRD_RD8081_RECTANGLE_HPP

#include <iosfwd>
#include "shapes.hpp"

namespace ilrd
{

class Rectangle : public Shape
{
public:
    Rectangle(double m_width, double m_height, double angle, Point center);
    //virtual ~Rectangle();
    //Rectangle(const Point&) = default;
    //Rectangle& operator=(const Point&) = default;
    
    virtual Rectangle& Rotate(double angle) =0;
    virtual Rectangle& Revolve(const Point& pivot, double angle) =0;
    virtual const Point& GetPosition() const;
    virtual void SetPosition(const Point& other) =0;
    virtual const double& GetAngle() const;
    virtual void SetAngle(double new_angle);
    
private:
    double m_width;
    double m_height;
};

} //namespae ilrd

#endif // Rectangle
