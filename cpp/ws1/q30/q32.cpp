#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_)
    {
    
    }
};

void myterminate () 
{
    std::cerr << "terminate handler called\n";
    abort();  // forces abnormal termination
}

void Fifi()
{
    throw 'x'; 
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
//    B x1(3);
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main()
{
    std::set_terminate (myterminate);
    try 
    {
        Bar();
    }
    
    catch (bad_alloc&)
    {
        cerr << "Out of memory! exiting."; 
        exit(2);
    }
    
    catch (BadDog& b)
    {
        cerr << "Bad dog exception: " << b.what();
        exit(3);
    }
    
    catch (exception& r)
    {
        cerr << "unknown exception: " << r.what();
        exit(4);
    }
     
    return 0;
}
