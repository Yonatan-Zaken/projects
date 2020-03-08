#include <iostream>
#include <typeinfo>
#include <stdio.h>
using namespace std;

int i = 8;
int& ip = i;

void Foo(int& arg1, char& arg2)
{
    cout << "In Foo arg1 = " << arg1 << " " << "arg2 = " << arg2 << "\n"; 
}

/*
struct Test
{
    char& c = ch;
    float& f = fl;
    int i = 3;
}; 
*/  
int main()
{
    ip = 9;
    char c = 'a';
    char& r_c = c;
    char *pc = &r_c;
    
    Foo(i, c);
    
    cout << sizeof(ip) << "\n";
    cout << &ip << "\n";
    cout << &i << "\n";
    cout << i << "\n";
    cout << r_c << "\n";
}

