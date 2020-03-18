#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <new>
#include <typeinfo>

using namespace std;

class X
{
public:
     X(int a_ = 1) : m_a(a_){}
     ~X();
private:
    int m_a;
};

int Foo(int) throw(bad_alloc)
{
    throw bad_alloc();
}

void Bar() throw(bad_cast)
{
    throw 5;       
}

X::~X()
{
    cerr << Foo(m_a) << endl;
}

void Fishi()
{
    X x1;
    
    Bar();

}

int main()
{
    Fishi();
     
    return 0;
}
