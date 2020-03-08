#include <iostream>
using namespace std;

int bar()
{
    cout << "It Worked!" << endl;
    return 2;
}

void foo(int a, int i = bar(), float j = 4)
{
    
    cout << "a = " << a << endl;         
    cout << i << endl;
    cout << j << endl;              
}


int main()
{
    foo(55, );
    
    return 0;
}

