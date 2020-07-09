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
private:
    class CharProxy;
    
public:
    RCString(const char *str = ""); // implicit convertor 
    ~RCString() noexcept; // dtor
    RCString(const RCString& other) noexcept; // cctor
    RCString& operator=(const RCString& other);  // assignment operator

    std::size_t Length() const noexcept;
    const char *GetCStr() const noexcept;          
    
    RCString& operator+=(const RCString& other); 
    CharProxy operator[](std::size_t index);
    char operator[](std::size_t index) const noexcept;

    static std::istream& operator>>(std::istream& is, RCString& rcstr);    

    static const size_t RCSTR_BUFFER_SIZE = 75;
    
private:
    char *m_rcstr;
    
    class CharProxy
    {
    public: 
        CharProxy(RCString& ,size_t index); // ctor
        CharProxy& operator=(char c); // assignment operator
        operator char(); // convertor operator 
        // using compiler generated cctor
        // using compiler generated dtor
    
    private:
        RCString& m_prx_rcstr;
        size_t m_prx_index;
    };
    
};

std::ostream& operator<<(std::ostream& os, const RCString& rcstr) noexcept;
//std::istream& operator>>(std::istream& is, RCString& rcstr);
bool operator==(const RCString& lhs, const RCString& rhs) noexcept;
bool operator!=(const RCString& lhs, const RCString& rhs) noexcept;
bool operator>(const RCString& lhs, const RCString& rhs) noexcept;
bool operator<(const RCString& lhs, const RCString& rhs) noexcept;
const RCString operator+(const RCString& lhs, const RCString& rhs);

} // namespace ilrd

#endif // ILRD_RD8081_REFERENCE_COUNTER_STRING_HPP
