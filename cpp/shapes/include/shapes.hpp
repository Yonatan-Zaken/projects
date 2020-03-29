/*******************************
    Shapes 
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_SHAPE_HPP
#define ILRD_RD8081_SHAPE_HPP

#include <iosfwd>
#include "point.hpp"

namespace ilrd
{

class Shape
{
public:
    Shape(Point center, double angle);
    virtual ~Shape();
    //Shape(const Point&) = default;
    //Shape& operator=(const Point&) = default;
    
    virtual Shape& Rotate(double angle) =0;
    virtual Shape& Revolve(const Point& pivot, double angle) =0;
    virtual const Point& GetPosition() const;
    virtual void SetPosition(const Point& other) =0;
    virtual const double& GetAngle() const;
    virtual void SetAngle(double new_angle);
    
private:
    Point m_center_position;
    double m_angle;
};

} //namespae ilrd

#endif // SHAPE
