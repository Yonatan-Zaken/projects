#include <iostream>

class X
{
public:
    X() : m_id(++s_cntr) {}
    int GetId(); 
    
private:
    int m_id;
    static int s_cntr;
};

int X::s_cntr = 0;

int X::GetId() 
{
    std::cout << m_id << std::endl;
    return s_cntr;
}

int main()
{
    X x1;
    X x2;
    
    x1.GetId();
    x2.GetId();
     
    return 0;
}
