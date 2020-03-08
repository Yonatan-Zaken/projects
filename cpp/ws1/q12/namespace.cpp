#include <iostream>
using namespace std;

// namespaces
namespace useless
{
    unsigned int g_wasteful[400] = {0};
    extern int g_notthere;
    void Foo() {cout << "using Foo of useless\n";}
    
    namespace wasteoftyme
    {
        void Foo() {cout << "using Foo of wasteoftyme\n";}
    } //namespace wasteoftyme
} //namespace useless

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
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() {cout << "using Foo of global scope\n";}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    ::Foo(); //try uncommenting and solve error
    Bar(); //why no error?
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
} //namespace useless

int main()
{
    DoStuff();
    DoMoreStuff();
    DoUselessStuff();
    
    return 0;
}
