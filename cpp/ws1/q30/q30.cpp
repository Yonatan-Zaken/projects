#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;
/* 
class exception {
public:
  exception () throw();
  exception (const exception&) throw();
  exception& operator= (const exception&) throw();
  virtual ~exception() throw();
  virtual const char* what() const throw();
}

class runtime_error : public exception {
public:
  explicit runtime_error (const string& what_arg);

constructor:
The string passed as what_arg has the same content 
as the value returned by member what.

The class inherits the what member function from exception.
};*/

class B
{
public:
    explicit B(int a_): m_a(a_)
    {
        cout << "B Ctor\n";
    }
    
    ~B()
    {
        cout << "B Dtor\n";
    }
    
private:
    int m_a;
};

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_)
    {
    
    }
};

void Fifi()
{
    throw BadDog("bad pup"); 
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    B x1(3);
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
