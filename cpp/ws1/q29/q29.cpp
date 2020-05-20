#include <iostream>

class B
{
public:
    B(int a_ = 3): m_a(a_)
    {
        std::cout << "B::Ctor" << std::endl;
    }
    
    virtual ~B()
    {
        std::cout << "B::Dtor" << std::endl;
    }
    
    virtual void Print1() const;
    virtual void Print2() const;
    virtual void Print3() const;

private:
    int m_a;
};

void B::Print1() const
{
    std::cout << "B::Print1 B::m_a - " << m_a << std::endl;
}

void B::Print2() const
{
    std::cout << "B::Print2" << std::endl;
}

void B::Print3() const
{
    std::cout << "B::Print3" << std::endl;
}

class X: public B
{
public:
    X(): m_b(0) 
    {
        std::cout << "X::Ctor" << std::endl;
    }
    
    ~X()
    {
        std::cout << "X::Dtor" << std::endl;
    }
    
    virtual void Print1() const
    {
        std::cout << "X::Print1 X::m_b - " << m_b << std::endl;
        B::Print1();
        std::cout << "X::Print1 end" << std::endl;        
    }
    
    void Print2() const 
    {
        std::cout << "X::Print2" << std::endl;
    }

private:
    int m_b;
};

int main()
{
    B *b1 = new B;
    B *b2 = new X;
    X x1;
    B *b3 = &x1;
    B base; 
    X *d1 = &base;

    std::cout << std::endl << "main b1:" << std::endl;
    b1->Print1();      
    b1->Print2();        
    b1->Print3();
    
    std::cout << std::endl << "main b2:" << std::endl;
    b2->Print1();      
    b2->Print2();        
    b2->Print3();
    
    std::cout << "testing something\n";

    b3->Print1();
    b3->Print2();
    b3->Print3();
    
    X *xx = static_cast<X*>(b2);
    std::cout << std::endl << "main xx:" << std::endl;
    xx->Print2();
    b2->Print2();
    
    delete b1;
    delete b2;
    
    return 0;
}


