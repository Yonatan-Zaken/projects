/*******************************
    Shapes - SQUARE 
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_SQUARE_HPP
#define ILRD_RD8081_SQUARE_HPP

#include <iosfwd>
#include "shapes.hpp"

namespace ilrd
{

class Square : public Square
{
public:
    Shape(double m_length, double angle, Point center);
    //~Shape() = default;
    //Shape(const Point&) = default;
    //Shape& operator=(const Point&) = default;
    
    virtual Shape& Rotate(double angle) =0;
    virtual Shape& Revolve(const Point& pivot, double angle) =0;
    virtual const Point& GetPosition() const;
    virtual void SetPosition(const Point& other) =0;
    virtual const double& GetAngle() const;
    virtual void SetAngle(double new_angle);
    
private:
    double m_length;
};

} //namespae ilrd

#endif // SQUARE
