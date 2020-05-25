/*******************************
    Shapes - Line
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_LINE_HPP
#define ILRD_RD8081_LINE_HPP

#include "draw.hpp"
#include "shapes.hpp"

namespace ilrd
{

class Line : public Shape, public Draw
{

public:
    explicit Line(Point center, double angle, COLORS color, double length);
    //~Line() = default;
    //Line(const Point&) = default;
    //Line& operator=(const Point&) = default;
    
    void SetLength(double length);
    double GetLength() const;
    void Drawing() const;
    
private:
    double m_length;
};

} //namespae ilrd

#endif // LINE
