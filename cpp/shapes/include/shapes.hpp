/*******************************
    Shapes 
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_SHAPE_HPP
#define ILRD_RD8081_SHAPE_HPP

#include "point.hpp"

namespace ilrd
{

class Shape
{

public:
    Shape(Point center, double angle);
    virtual ~Shape() =0;
    //Shape(const Point&) = default;
    //Shape& operator=(const Point&) = default;
    
    virtual Shape& Rotate(double angle);
    virtual Shape& Revolve(const Point& pivot, double angle);
    virtual const Point& GetPosition() const;
    virtual void SetPosition(const Point& other);
    virtual const double& GetAngle() const;
    virtual void SetAngle(double new_angle);
    static const double PI; 
    
private:
    Point m_center_position;
    double m_angle;
};

} //namespae ilrd

#endif // SHAPE
