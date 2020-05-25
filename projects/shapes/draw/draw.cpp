/*******************************
    Shapes - Line
    CPP File
    26/03/2020
    ILRD - RD8081               
*******************************/

#include "draw.hpp" 

namespace ilrd
{

const double Draw::PI = 3.14159265;

Draw::Draw(COLORS color): m_color(color) 
{}

Draw::~Draw() noexcept
{}
    
void Draw::SetColor(COLORS color) noexcept
{
    m_color = color;
}

COLORS Draw::GetColor() const noexcept
{
    return m_color;
}

} // namespace ilrd
