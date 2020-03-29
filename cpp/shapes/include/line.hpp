/*******************************
    Shapes - Line
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_LINE_HPP
#define ILRD_RD8081_LINE_HPP

#include <iosfwd>
#include "shapes.hpp"

namespace ilrd
{

class Line : public Shape
{

public:
    Line(double length, double angle, Point center);
    //~Line() = default;
    //Line(const Point&) = default;
    //Line& operator=(const Point&) = default;
    
    virtual Shape& Rotate(double angle);
    virtual Shape& Revolve(const Point& pivot, double angle);
//    virtual const Point& GetPosition() const;
    virtual void SetPosition(const Point& other);
//    virtual const double& GetAngle() const;
//    virtual void SetAngle(double new_angle);
    
private:
    double m_length;
};

} //namespae ilrd

#endif // LINE
