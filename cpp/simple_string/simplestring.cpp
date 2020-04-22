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
#include <exception>


#include "simplestring.hpp"
using namespace ilrd;

/******************************* Static Functions *****************************/

static char* Strdup(const char *str)
{
    size_t length = strlen(str);
    char *ptr = new char[length + 1];
    memcpy(ptr, str, sizeof(char) * (length + 1));
    
    return ptr;
}

/******************************* Ctors and Dtor *******************************/

String::String(const char *str): m_cstr(Strdup(str))
{
}

String::String(const String& other_): m_cstr(Strdup(other_.m_cstr))
{
}

String::~String()
{
    delete[] m_cstr;
    m_cstr = NULL;
}

/**************************** Operator Functions ******************************/

String& String::operator=(const String& other_)
{
    delete [] m_cstr;
    m_cstr = NULL;
    m_cstr = Strdup(other_.m_cstr);

    return *this;
}

bool ilrd::operator>(const String& str1, const String& str2)
{
    return (0 < strcmp(str1.Cstr(), str2.Cstr()));
}

bool ilrd::operator<(const String& str1, const String& str2)
{
    return (0 > strcmp(str1.Cstr(), str2.Cstr()));
}

bool ilrd::operator==(const String& str1, const String& str2)
{
    return (0 == strcmp(str1.Cstr(), str2.Cstr()));
}

std::ostream& ilrd::operator<<(std::ostream& os_, const String& other_)
{
    return (os_ << other_.Cstr());
} 

/***************************** Member Functions *******************************/

size_t String::Length() const
{
    return strlen(m_cstr);
}

const char *String::Cstr() const
{
    return m_cstr;
}

char *String::Cstr() 
{
    return m_cstr;
}
