/*******************************
    Shapes 
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_SHAPE_HPP
#define ILRD_RD8081_SHAPE_HPP

#include "utility.hpp" // noexcept
#include "point.hpp"

namespace ilrd
{

class Shape
{

public:
    Shape(const Point& center, double angle = 0);
    virtual ~Shape() noexcept =0;
    //Shape(const Point&) = default;
    //Shape& operator=(const Point&) = default;
    
    void Rotate(double angle) noexcept;
    void Revolve(const Point& pivot, double angle);
    Point GetPosition() const noexcept;
    void SetPosition(const Point& other) noexcept;
    double GetAngle() const noexcept;
    void SetAngle(double new_angle) noexcept;
   
private:
    Point m_center_position;
    double m_angle;
};

} //namespae ilrd

#endif // SHAPE
