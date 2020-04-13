/***********************
    File
    Header File
    07/04/2020
    ILRD - RD8081               
***********************/

#ifndef ILRD_RD8081_FILE_HPP
#define ILRD_RD8081_FILE_HPP

#include <string> // string

#include "utility.hpp" // noexcept
#include "entry.hpp"   // Entry

namespace ilrd
{

class File: public Entry
{
public:
    explicit File(std::string filename);  
    virtual ~File() noexcept; 

    virtual void Display(int level) const noexcept;
 
private:
    std::string m_filename; 

    File(const File&); // = disabled
    File& operator=(const File&); // = disabled    
};

} // namespace ilrd

#endif // ILRD_RD8081_FILE_HPP
