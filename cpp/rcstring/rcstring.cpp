/*******************************
    Reference Counter String
    CPP File
    17/03/2020
    ILRD - RD8081               
*******************************/
#include <iostream> // cout
#include <cstring> // strcpy

#include "rcstring.hpp"

/******************************* Static Functions *****************************/

static char* Strdup(const char *str)
{
    size_t length = strlen(str);
    char *ptr = new char[length + 1];
    memcpy(ptr, str, sizeof(char) * (length + 1));
    
    return ptr;
}

/******************************* Ctors and Dtor *******************************/

RCString::RCString(const char *str): m_cstr(Strdup(str))
{
}

RCString(const rcstring& other)
{

}

RCString& operator=(const rcstring& other)
{

}

~RCString()
{
    delete []
}

/***************************** Member Functions *******************************/

size_t RCString::Length() const
{
    return strlen(m_cstr);
}

const char *RCString::GetCstr() const
{
    
}

char *RCString::GetCstr() 
{
    
}

/**************************** Operator Functions ******************************/

RCString& operator+=(const RCString& other)
{

}

const RCString operator+(const RCString& lhs, const RCString& rhs)
{

}

bool operator==(const RCString& lhs, const RCString& rhs)
{

}

bool operator!=(const RCString& lhs, const RCString& rhs)
{

}

bool operator>(const RCString& lhs, const RCString& rhs)
{

}

bool operator<(const RCString& lhs, const RCString& rhs)
{

}

char& operator[](std::size_t index)
{

}

char operator[](std::size_t index) const // ???
{

}

std::ostream& operator<<(std::ostream& os, const RCString& str)
{

}

std::istream& operator>>(std::istream& is, RCString& str)
{

}

































