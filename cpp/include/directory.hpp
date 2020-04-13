/***********************
    Directory
    Header File
    07/04/2020
    ILRD - RD8081               
***********************/

#ifndef ILRD_RD8081_DIRECTORY_HPP
#define ILRD_RD8081_DIRECTORY_HPP

#include <string> // string
#include <vector> // vector

#include "utility.hpp" // noexcept
#include "entry.hpp" // Entry

namespace ilrd
{

class Directory: public Entry
{
public:
    explicit Directory(std::string dirname); 
    virtual ~Directory() noexcept;

    virtual void Display(int level) const noexcept;
    void AddEntry(const Entry *);
 
private:
    std::string m_dirname; 
    std::vector<const Entry *> m_entry_list;

    Directory(const Directory&); // = disabled
    Directory& operator=(const Directory&); // = disabled    
};

} // namespace ilrd

#endif // ILRD_RD8081_DIRECTORY_HPP
