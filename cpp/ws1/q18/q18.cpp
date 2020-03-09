#include <iostream>
#include <stdio.h>
using namespace std;

void Foo(const double& param)
{
/*    cout << "Foo Check" << reinterpret_cast<const int&>(param) << "\n";*/
    cout << (size_t)&param << "\n";
    cout << param << "\n";
}
void Bar(double& param)
{
    cout << (size_t)&param << "\n";
    cout << param << "\n";
}

int main()
{
    int x = 5;
    double d = 155.5;
    
    cout << (size_t)&x << "\n";
    Foo(x);
    Bar(x);
    Bar(reinterpret_cast<double&>(x));
    
    
    return 0;
}

