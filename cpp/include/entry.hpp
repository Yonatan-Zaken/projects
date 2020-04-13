/***********************
    Entry
    Header File
    07/04/2020
    ILRD - RD8081               
***********************/

#ifndef ILRD_RD8081_ENTRY_HPP
#define ILRD_RD8081_ENTRY_HPP

#include "utility.hpp" // noexcept

namespace ilrd
{

class Entry
{
public:
    explicit Entry() { };
    virtual ~Entry() noexcept { };
    virtual void Display(int level) const noexcept = 0;

private:
    Entry(const Entry&); // = disabled
    Entry& operator=(const Entry&); // = disabled
};

} // namespace ilrd

#endif // ILRD_RD8081_ENTRY_HPP
