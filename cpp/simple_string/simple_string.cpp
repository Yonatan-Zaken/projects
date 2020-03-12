/*********************************/
/*   			             	 */
/*   CPP		                 */
/*   Simple String               */
/*   Author: Yonatan Zaken       */
/*   Last Updated 11/3/20        */
/*   Reviewed by: Gidron         */   
/*			                   	 */
/*********************************/
#include <iostream> // cout
#include <cstring> // strcpy

#include "simple_string.hpp"

/******************************* Ctors and Dtor *******************************/

String::String()
{
    std::cout << "deafault ctor\n";
}

String::String(const char *str): m_cstr(new char[strlen(str) + 1])
{
    strcpy(m_cstr, str);
}

String::String(const String& other_): m_cstr(new char[strlen(other_.m_cstr) + 1])
{
    strcpy(m_cstr, other_.m_cstr);
}

String::~String()
{
    delete []m_cstr;
    m_cstr = NULL;
}

/*************************** Operator Functions ******************************/

String& String::operator=(const String& other_)
{
    delete [](m_cstr);
    m_cstr = NULL;
    m_cstr = new char[strlen(other_.m_cstr) + 1];
    strcpy(m_cstr, other_.m_cstr);

    return *this;
}

bool String::operator>(const String& other_)
{
    return (0 < strcmp(m_cstr, other_.m_cstr));
}

bool String::operator<(const String& other_)
{
    return (0 > strcmp(m_cstr, other_.m_cstr));
}

bool String::operator==(const String& other_)
{
    return (0 == strcmp(m_cstr, other_.m_cstr));
}

std::ostream& operator<<(std::ostream& os_, const String& other_)
{
    return (os_ << other_.m_cstr);
} 

/***************************** Member Functions *******************************/

size_t String::Length() const
{
    return strlen(m_cstr);
}

char *String::Cstr() const
{
    return m_cstr;
}
