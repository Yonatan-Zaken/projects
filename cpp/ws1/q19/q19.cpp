#include <iostream>
using namespace std;

struct X
{
    explicit X(); // defualt ctor
    explicit X(int a_, int b_ = 8); // regular ctor
    ~X(); // dtor
    X(const X& other_); // copy ctor
    X& operator=(const X& other_); // assignment operator
    int m_a;
    const int m_b;
};

X::X(): m_a(3), m_b(4) // imp default ctor
{
    // m_a = 3;
    // m_b = 4;
    cout << "this:" << this << " X int int Ctor. m_a:" << m_a << " m_b:" << m_b << endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_) // imp second ctor
{
    cout << "this:" << this << " X int int Ctor. m_a:" << m_a << " m_b:" << m_b << endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) // imp copy ctor
{
    cout << "this:" << this << " X copy Ctor. m_a:" << m_a << " m_b:" << m_b << endl;
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    //m_b = other_.m_b;
    cout << "this:" << this << " X assignment operator m_a:" << m_a << " does not change m_b:" << m_b << endl;
    return *this;
}

X::~X()
{
    cout << "this:" << this << " X Dtor. m_a:" << m_a << " m_b:" << m_b << endl;
}

int main()
{
    X x1;
    X x2(7);
    X *px = new X(x2);
    X x3(9,10);
    X x4(x1);
    
    int i(5.44);
    
    x1 = x3;
    
    delete px; px = 0;
    return 0;
}



