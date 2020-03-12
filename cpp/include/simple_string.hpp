#ifndef ILRD__RD81_SIMPLE_STRING_HPP
#define ILRD__RD81_SIMPLE_STRING_HPP

namespace ilrd
{

class String;
std::ostream& operator<<(std::ostream& os_, const String& other_);

class String
{
public:
    explicit String(); // ctor
    explicit String(const char* ); // ctor
    String(const String& other_); // cctor
    String& operator=(const String& other_); // assignment operator
    ~String(); //dtor
    
    bool operator==(const String& other_);
    bool operator>(const String& other_);
    bool operator<(const String& other_);
    friend std::ostream& operator<<(std::ostream& os_, const String& other_);
    
    size_t Length() const;
    char *Cstr() const;
    
private:
    char *m_cstr;
};

}// namespace ilrd

#endif
