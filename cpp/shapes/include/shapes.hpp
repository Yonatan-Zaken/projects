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
    
    void Rotate(double angle);
    void Revolve(const Point& pivot, double angle);
    Point GetPosition() const;
    void SetPosition(const Point& other);
    double GetAngle() const;
    void SetAngle(double new_angle);
   
    
private:
    Point m_center_position;
    double m_angle;
};

} //namespae ilrd

#endif // SHAPE
