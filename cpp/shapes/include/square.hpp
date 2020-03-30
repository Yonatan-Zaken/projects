/*******************************
    Shapes - Square 
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_SQUARE_HPP
#define ILRD_RD8081_SQUARE_HPP

#include "draw.hpp"
#include "shapes.hpp"

namespace ilrd
{

class Square : public Shape, public Draw
{
public:
    explicit Square(Point center, double angle, COLORS color, double length);
    //~Shape() = default;
    //Shape(const Point&) = default;
    //Shape& operator=(const Point&) = default;
    
    double GetLength() const;
    void SetLength(double length);
    void Drawing() const;
    
private:
    double m_length;
};

} //namespae ilrd

#endif // SQUARE
