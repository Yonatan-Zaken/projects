#include <iostream>

using namespace std;

void Foo(int a)
{
    cout << "Foo - value of int is: " << a << endl;
}

void Foo(char c, int a)
{
    cout << "Foo - value of char is: " << c << endl;
    cout << "Foo - value of int is: " << a << endl;
}

void Bar(float b)
{
    cout << "Bar - value of float is: " << b << endl;
}


