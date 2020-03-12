#include <iostream>

struct X
{
    /*explicit X();*/
    /*~X(); // dtor*/
    int m_a;
    char m_b;
};


    int *m_b;
};

/*
struct Y
{
    X m_x;
    int m_i;
};

X::~X()
{
    std::cout << "this:" << this << " X Dtor. m_a:" << m_a << " m_b:" << m_b << std::endl;
}
*/

int main()
{
    X x1;
    X x2(x1);
    X x3;
    x3 = x1;
    
    /*
    X x2(x1);
    X x3;
    x3 = x1;
    */
    return 0;
}


