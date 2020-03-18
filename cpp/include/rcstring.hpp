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
    ~RCString() noexcept;
    RCString(const RCString& other);
    RCString& operator=(const RCString& other);   

    std::size_t Length() const;
    const char *GetCStr() const;
    char *GetCStr(); // time complexity O(n)           
    
    RCString& operator+=(const RCString& other); 
    char& operator[](std::size_t index);
    char operator[](std::size_t index) const; // ???
    
    s1("moshe");
    std::cout << s1[1];
    s1[1] = 'h';

private:
    char *m_cstr;
    std::size_t *m_count;
};

std::ostream& operator<<(std::ostream& os, const RCString& str);
std::istream& operator>>(std::istream& is, RCString& str);
bool operator==(const RCString& lhs, const RCString& rhs);
bool operator!=(const RCString& lhs, const RCString& rhs);
bool operator>(const RCString& lhs, const RCString& rhs);
bool operator<(const RCString& lhs, const RCString& rhs);
const RCString operator+(const RCString& lhs, const RCString& rhs);

} // namespace ilrd

#endif // ILRD_RD8081_REFERENCE_COUNTER_STRING_HPP
