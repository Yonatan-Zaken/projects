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
    explicit Square();
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

std::ostream& operator<<(std::ostream& os, const Square& square)
{
    os << "Squre ";
    os << square.GetPosition();
    os << square.GetAngle();
    os << square.GetColor();
    os << square.GetLength();

    return os;
}

} //namespae ilrd

#endif // SQUARE
