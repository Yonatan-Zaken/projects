#include <cstring>  // memcpy
#include <iostream> // cout

class String
{
private:
    class CharProxy;    
public:
    String(const char *str = "ABC");
    String(const String&);
    void operator=(const String&);
    void operator=(const char);
    CharProxy operator[](size_t index);
    ~String();    
    
    const char *GetCStr() const;
    static size_t GetInstances();

private:
    char *m_cstr;
    char *StrDup(const char *);
    static size_t counter;
    
    class CharProxy
    {
    public:
        CharProxy(String&, size_t index);
        CharProxy& operator=(char c);
        CharProxy& operator=(const CharProxy& other_);
        operator char() const;
        
    private:
        String& m_prx_string;
        size_t m_prx_index;
    };
    
};

size_t String::counter = 0;

/******************************************************************************/

int main ()
{
    String s1;
    s1 = "testing";
    s1 = '#';
    String s2(s1);
    String s3("checking");
    s2 = s3;
    std::cout << s2.GetCStr() << "\n";
    std::cout << "num of obj: " << s1.GetInstances() << "\n";
    s2[0] = 'r';
    std::cout << s2.GetCStr() << "\n";
    std::cout << s2[3] << "\n";
    std::cout << s1.GetCStr() << "\n";
    s2[3] = s1[2];
    std::cout << s2.GetCStr() << "\n";
    
    return 0;
}

/******************************* Char Proxy ***********************************/

String::CharProxy::CharProxy(String& str, size_t index): 
    m_prx_string(str), 
    m_prx_index(index)
{}

String::CharProxy& String::CharProxy::operator=(char c)
{
    m_prx_string.m_cstr[m_prx_index] = c;
    return *this;
}

String::CharProxy& String::CharProxy::operator=(const CharProxy& other_)
{
    m_prx_string.m_cstr[m_prx_index] = other_.m_prx_string.m_cstr[other_.m_prx_index];
    return *this;
}

String::CharProxy::operator char() const
{
    return (m_prx_string.m_cstr[m_prx_index]);
}

/******************************* String API ***********************************/

String::String(const char *str): m_cstr(StrDup(str))
{
    ++counter;
}

/******************************************************************************/

String::String(const String& other_): m_cstr(StrDup(other_.m_cstr))
{
    ++counter;
}

/******************************************************************************/

void String::operator=(const String& other_)
{
    delete[] m_cstr; m_cstr = NULL;
    m_cstr = StrDup(other_.m_cstr);
}

/******************************************************************************/

void String::operator=(const char c)
{
    memset(m_cstr, c, strlen(m_cstr));
}

/******************************************************************************/

String::CharProxy String::operator[](size_t index)
{
    return String::CharProxy(*this, index);
}

/******************************************************************************/

String::~String()
{
    delete[] m_cstr; m_cstr = NULL;
    --counter;
}

/******************************************************************************/

const char *String::GetCStr() const
{
    return m_cstr;
}

/******************************************************************************/

size_t String::GetInstances() 
{
    return counter;
}

/******************************************************************************/

char *String::StrDup(const char* str)
{
    size_t size = strlen(str) + 1;
    char *buffer = new char[size];
    memcpy(buffer, str, size);
    
    return buffer;
}
