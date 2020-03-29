/*******************************
    Shapes - Line
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "draw.hpp" 

namespace ilrd
{

Draw::Draw(COLORS color): m_color(color)
{
}

Draw::~Draw()
{
}
    
void Draw::SetColor(COLORS color)
{
    m_color = color;
}

COLORS Draw::GetColor() const
{
    return m_color;
}

} // namespace ilrd
