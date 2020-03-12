#include <iostream>

struct X
{
    explicit X(int);
    ~X();
    
    void Foo();
    void Bar() const;

    int m_a;
    int *m_p;
};

X::X(int a_): m_a(a_), m_p(new int(a_))
{

}

X::~X()
{
    delete m_p; m_p = 0;    
}

void X::Foo()
{
    ++m_a;
    --(*m_p);
}

void X::Bar() const
{ 
    std::cout << m_a << std::endl;
    std::cout << *m_p << std::endl;
    std::cout << m_p << std::endl;
    //m_a = 0; //---1---
    //m_p = 0; //---2---
    //*m_p = 0; //---3---
    ++m_p;
    //++m_p;

}

void Fifi(const X& x_)
{
    //x_.Foo(); //---4---
    x_.Foo(); //---4---
    x_.Bar();
}

int main()
{
    X x1(1);
    
    x1.Foo();
    
    Fifi(x1);
    
    return 0;
}
