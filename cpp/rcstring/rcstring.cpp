/*******************************
    Reference Counter String
    CPP File
    17/03/2020
    ILRD - RD8081               
*******************************/
#include <iostream> // cout
#include <cstring> // strcpy
#include <cassert> //assert

#include "rcstring.hpp" 

/************************ Static Functions Declarations ***********************/
static char *GoToString(char *str);
static size_t GetCounter(char *str);
static char* RCStrdup(const char *str);
/******************************************************************************/

namespace ilrd
{

/************************* Proxy Ctors and operators **************************/

RCString::CharProxy::CharProxy(RCString& rcstr, size_t index): 
m_prx_rcstr(rcstr), m_prx_index(index)
{
}

RCString::CharProxy& RCString::CharProxy::operator=(char c)
{
    char *duplicate = RCStrdup(GoToString(m_prx_rcstr.m_rcstr));
    m_prx_rcstr.~RCString();
    m_prx_rcstr.m_rcstr = duplicate;
    *(GoToString(m_prx_rcstr.m_rcstr) + m_prx_index) = c;
    
    return *this;        
}

RCString::CharProxy::operator char()
{
    return (*(m_prx_rcstr.GetCStr() + m_prx_index));
}

/*************************** RCString Ctors and Dtor **************************/

RCString::RCString(const char *str): m_rcstr(RCStrdup(str))
{
}

RCString::RCString(const RCString& other) noexcept: m_rcstr(other.m_rcstr) 
{
    ++(*reinterpret_cast<size_t *>(m_rcstr));
}

RCString& RCString::operator=(const RCString& other)
{
    char *duplicate = RCStrdup(GoToString(other.m_rcstr));
    this->~RCString(); 
    m_rcstr = duplicate;
    
    return *this;
}

RCString::~RCString() noexcept
{
    --(*reinterpret_cast<size_t*>(m_rcstr));  
    if (0 == GetCounter(m_rcstr))
    {
        delete[] m_rcstr;
        m_rcstr = NULL;    
    }
}

/***************************** Member Functions *******************************/

size_t RCString::Length() const noexcept
{
    return strlen(GoToString(m_rcstr));
}

const char *RCString::GetCStr() const noexcept
{
    return GoToString(m_rcstr);    
}

/**************************** Operator Functions ******************************/

RCString& RCString::operator+=(const RCString& other)
{
    size_t length_member = strlen(GoToString(m_rcstr));
    size_t length_other = strlen(GoToString(other.m_rcstr)) + 1;
    
    char *concat_string = new char[length_member + length_other + sizeof(size_t)];
    memcpy(GoToString(concat_string), GoToString(m_rcstr), 
                            sizeof(char) * length_member);
    memcpy(GoToString(concat_string) + length_member, GoToString(other.m_rcstr),       
                                                   sizeof(char) * length_other);
    
    (*reinterpret_cast<size_t *>(concat_string)) = 1;
    this->~RCString();
    m_rcstr = concat_string;
     
    return *this;
}

const RCString operator+(const RCString& lhs, const RCString& rhs)
{
    return (RCString(lhs.GetCStr()) += rhs);    
}

bool operator==(const RCString& lhs, const RCString& rhs) noexcept
{
    return (0 == strcmp(lhs.GetCStr(), rhs.GetCStr())); 
}

bool operator!=(const RCString& lhs, const RCString& rhs) noexcept
{
    return (!(lhs == rhs));
}

bool operator>(const RCString& lhs, const RCString& rhs) noexcept
{
    return (0 < strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

bool operator<(const RCString& lhs, const RCString& rhs) noexcept
{
    return (0 > strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

RCString::CharProxy RCString::operator[](std::size_t index) 
{
    assert(strlen(GoToString(m_rcstr)) >= index);
 
    return RCString::CharProxy(*this, index);
}

char RCString::operator[](std::size_t index) const noexcept  
{
    assert(strlen(GoToString(m_rcstr)) >= index);
    
    return (*(GoToString(m_rcstr) + index));
}

std::ostream& operator<<(std::ostream& os, const RCString& rcstr) noexcept
{
    return (os << rcstr.GetCStr());
}

std::istream& RCString::operator>>(std::istream& is, RCString& rcstr)
{
    char *buffer = new char[RCString::RCSTR_BUFFER_SIZE];
    is >> buffer;
    rcstr = buffer;   
    delete[] buffer;
    
    return is;
}

} // namespace ilrd

/**************************** Static Functions ******************************/
static char *GoToString(char *str)
{
    return (str + sizeof(size_t));
} 

static size_t GetCounter(char *str)
{
    return (*reinterpret_cast<size_t*>(str));
} 

static char* RCStrdup(const char *str)
{
    size_t length = strlen(str) + 1;
    char *ptr = new char[length + sizeof(size_t)];
    memcpy(GoToString(ptr), str, sizeof(char) * length);
    *reinterpret_cast<size_t *>(ptr) = 1;
    
    return ptr;
}
