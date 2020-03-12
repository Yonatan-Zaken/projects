#ifndef ILRD__RD81_SIMPLE_STRING_HPP
#define ILRD__RD81_SIMPLE_STRING_HPP

class String
{
public:
    explicit String(); // ctor
    explicit String(const char* ); // ctor
    String(const String& other_); // cctor
    String& operator=(const String& other_); // assignment operator
    ~String(); //dtor

    size_t Length() const;
    char *Cstr() const;
    
private:
    char *m_cstr;
    friend std::ostream& operator<<(std::ostream& os_, const String& other_);
    friend bool operator==(const String& s1, const String& s2);
    friend bool operator>(const String& s1, const String& s2);
    friend bool operator<(const String& s1, const String& s2);
};

#endif
