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

rcstring& operator=(const rcstring& other)
{

}

~rcstring()
{

}

