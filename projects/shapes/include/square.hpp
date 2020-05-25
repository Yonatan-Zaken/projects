/*******************************
    Shapes - Square 
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_SQUARE_HPP
#define ILRD_RD8081_SQUARE_HPP

#include <boost/shared_ptr.hpp>

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
    
    std::ostream& operator<<(std::ostream& os, const Square& square)
    {
        os << "Squre ";
        os << circle.GetPosition().GetX() << " ";
        os << circle.GetPosition().GetY() << " ";
        os << square.GetAngle() << " ";
        os << square.GetColor() << " ";
        os << square.GetLength() << " ";

        return os;
    }

    boost::shared_ptr<Square> CreateSquare(std::istream& is)
    {

    }

    double GetLength() const;
    void SetLength(double length);
    void Drawing() const;
    
private:
    double m_length;
};

} //namespae ilrd

#endif // SQUARE
