/*******************************
    Shapes - Rectangle
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_RECTANGLE_HPP
#define ILRD_RD8081_RECTANGLE_HPP

#include "draw.hpp"
#include "shapes.hpp"

namespace ilrd
{

class Rectangle : public Shape, public Draw
{
public:
    
    explicit Rectangle(Point center, double angle, COLORS color, double width, double height);
    //virtual ~Rectangle() = defualt;
    //Rectangle(const Point&) = default;
    //Rectangle& operator=(const Point&) = default;
    
    double GetWidth() const;
    double GetHeight() const;
    void SetWidth(double width);
    void SetHeight(double height);
    void Drawing() const;
    
private:
    double m_width;
    double m_height;
};

} //namespae ilrd

#endif // Rectangle
