/***********************
    File
    CPP File
    07/04/2020
    ILRD - RD8081               
***********************/
#include <iostream> // cout

#include "file.hpp" // file

namespace ilrd
{

File::File(std::string filename): m_filename(filename)
{}

File::~File() noexcept
{}

void File::Display(int level) const noexcept
{
    std::string buffer(level, HORIZONTAL_TAB);
    std::cout << buffer <<  m_filename << "\n";
}

} // namespace ilrd

