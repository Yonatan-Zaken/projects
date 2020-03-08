#include <iostream>

#include "header.hpp"

using namespace std;

namespace second
{
    int x = 11;
    int y = 22;
}

using namespace second;

int main () 
{
    cout << x << '\n';
    cout << y << '\n';
    /*cout << second::x << '\n';
    cout << second::y << '\n';*/
    return 0;
}
