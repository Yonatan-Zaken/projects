#include <iostream>

class X
{
public:
    X():m_a(5.22) {std::cout << "X ctor\n";}
    virtual ~X() {std::cout << "X dtor\n";}
    virtual void GetMem() {std::cout << m_a << "\n";}
private:
    double m_a;
};

class Y: public X
{
public: 
    Y():m_b(3) {std::cout << "Y ctor\n";}
    ~Y() {std::cout << "Y dtor\n";}
    void GetMem() {std::cout << m_b << "\n";}
private:
    int m_b;
};

void Foo(X& x)
{
    x.GetMem();
}

int main()
{
    Y y1;
    Foo(y1);
    
	return 0;
}
