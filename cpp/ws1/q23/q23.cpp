#include <iostream>

struct X
{
    X(int a_, int b_);
    
    void Inc();
    void Dec();
    int m_a;
    int m_b; 
};

X::X(int a_, int b_): m_a(a_), m_b(b_)
{
    std::cout << &(this->m_a);
    this->Inc();
}

void X::Inc()
{
    std::cout << "this Inc:" << this << std::endl;
    ++m_a;
    ++m_b;
}

void X::Dec()
{
    std::cout << "this Dec:" << this << std::endl;
    --m_a;
    --m_b;
}

void Inc()
{ 
    std::cout << "member function\n";    
}

int main()
{
    X x1(7, -55);
    X x2(x1);

    Inc();
    x1.Inc();
    x1.Inc();
    x2.Dec();
    
    return 0;
}
