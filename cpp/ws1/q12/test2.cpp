#include <iostream>
using namespace std;

namespace stupid
{
    void Foo() {cout << "using Foo of stupid\n";}
    void Bar() {}
    void DoNothing(unsigned int) {cout << "using DoNothing of stupid\n";}
} //namespace stupid

namespace useless
{
    void DoNothing(int) {cout << "using DoNothing of useless\n";}
} //namespace useless

using namespace useless;

void DoStuff()
{
    DoNothing(5);
}

using namespace stupid;

void DoMoreStuff()
{
    DoNothing(10);
}

int main()
{
    DoStuff();
    DoMoreStuff();

    return 0;
}
