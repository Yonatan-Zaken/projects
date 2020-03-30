/*******************************
    Draw
    Header File
    26/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_DRAW_HPP
#define ILRD_RD8081_DRAW_HPP

#include "glut_utils.h"

namespace ilrd
{

class Draw
{

public:
    Draw(COLORS color = COLOR_WHITE);
    virtual ~Draw();
    //Draw(const Point&) = default;
    //Draw& operator=(const Point&) = default;
    
    void SetColor(COLORS color);
    COLORS GetColor() const;
    virtual void Drawing() const =0;
    
    static const double PI; 
    
private:
    COLORS m_color;
};

} //namespae ilrd

#endif // DRAW
