/*******************************
    Reference Counter String
    Header File
    17/03/2020
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_REFERENCE_COUNTER_STRING_HPP
#define ILRD_RD8081_REFERENCE_COUNTER_STRING_HPP

#include <iosfwd> // ostream

#include "utility.hpp" // noexcept

namespace ilrd
{

class RCString
{
public:
    RCString(const char *str = ""); // implicit convertor constructor
    ~RCString() noexcept; // dtor
    RCString(const RCString& other); // cctor
    RCString& operator=(const RCString& other);  // copy assignment

    std::size_t Length() const;
    const char *GetCStr() const;          
    
    RCString& operator+=(const RCString& other); 
    char& operator[](std::size_t index);
    char operator[](std::size_t index) const;
    
private:
    char *m_rcstr;
};

std::ostream& operator<<(std::ostream& os, const RCString& rcstr);
std::istream& operator>>(std::istream& is, RCString& rcstr);
bool operator==(const RCString& lhs, const RCString& rhs);
bool operator!=(const RCString& lhs, const RCString& rhs);
bool operator>(const RCString& lhs, const RCString& rhs);
bool operator<(const RCString& lhs, const RCString& rhs);
const RCString operator+(const RCString& lhs, const RCString& rhs);

} // namespace ilrd

#endif // ILRD_RD8081_REFERENCE_COUNTER_STRING_HPP
