/*******************************
    Reference Counter String
    CPP File
    17/03/2020
    ILRD - RD8081               
*******************************/
#include <iostream> // cout
#include <cstring> // strcpy

#include "rcstring.hpp"

/************************ Static Functions Declarations ***********************/
static char *GoToString(char *str);
static size_t GetCounter(char *str);
static char* RCStrdup(const char *str);
/******************************************************************************/

namespace ilrd
{
/******************************* Ctors and Dtor *******************************/

RCString::RCString(const char *str): m_rcstr(RCStrdup(str))
{
}

RCString::RCString(const RCString& other): m_rcstr(other.m_rcstr) 
{
    ++(*reinterpret_cast<size_t *>(m_rcstr));
}

RCString& RCString::operator=(const RCString& other)
{
    if (&other != this)
    {
        delete[] m_rcstr;
        m_rcstr = NULL;
    }
    
    m_rcstr = other.m_rcstr;
    ++(*(reinterpret_cast<size_t *>(other.m_rcstr))); 
    
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

size_t RCString::Length() const
{
    return strlen(GoToString(m_rcstr));
}

const char *RCString::GetCStr() const
{
    return GoToString(m_rcstr);    
}
/*
char *RCString::GetCStr() 
{
    return GoToString(m_rcstr);    
}
*/
/**************************** Operator Functions ******************************/

RCString& RCString::operator+=(const RCString& other)
{
    size_t length_member = strlen(GoToString(m_rcstr));
    size_t length_other = strlen(GoToString(other.m_rcstr)) + 1;
    
    char *concat_string = new char[length_member + length_other + sizeof(size_t)];
    memcpy(GoToString(concat_string), GoToString(m_rcstr), length_member);
    memcpy(GoToString(concat_string) + length_member, GoToString(other.m_rcstr) , length_other);
    
    (*reinterpret_cast<size_t *>(concat_string)) = 1;
    --(*reinterpret_cast<size_t *>(m_rcstr));
    
    if (0 == GetCounter(m_rcstr))
    {
        delete[] m_rcstr;
        m_rcstr = NULL;
    }
    m_rcstr = concat_string;
     
    return *this;
}

const RCString operator+(const RCString& lhs, const RCString& rhs)
{
    RCString rcstr(lhs.GetCStr()); 
    rcstr += rhs;
    return rcstr;    
}

bool operator==(const RCString& lhs, const RCString& rhs)
{
    return (0 == strcmp(lhs.GetCStr(), rhs.GetCStr())); 
}

bool operator!=(const RCString& lhs, const RCString& rhs)
{
    return (!(lhs == rhs));
}

bool operator>(const RCString& lhs, const RCString& rhs)
{
    return (0 < strcmp(lhs.GetCStr(), rhs.GetCStr()));
}

bool operator<(const RCString& lhs, const RCString& rhs)
{
    return (!(lhs > rhs));
}

char& RCString::operator[](std::size_t index)
{
    char *duplicate_rcstr = RCStrdup(GoToString(m_rcstr));        
    --(*reinterpret_cast<size_t *>(m_rcstr));   
    
    if (0 == GetCounter(m_rcstr))
    {
        delete[] m_rcstr;
        m_rcstr = NULL;
    }
    
    m_rcstr = duplicate_rcstr;
    return (*(GoToString(m_rcstr) + index));
}

char RCString::operator[](std::size_t index) const 
{
    return (*(GoToString(m_rcstr) + index));
}

std::ostream& operator<<(std::ostream& os, const RCString& str)
{
    return (os << str.GetCStr());
}

std::istream& operator>>(std::istream& is, RCString& str)
{
    
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
