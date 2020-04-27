#include <iostream>

#include "utility.hpp"
#include "shared_ptr.hpp"
#include "point.hpp"

using namespace std;
using namespace ilrd;

struct Base
{
	Base(){ cout<< "ctor Base\n"; }
	virtual ~Base() { cout <<"dtor base\n"; }
	Base(const Base&) { cout<< "cctor Base\n"; }
	virtual void operator=(const Base&) {cout<< "= Base\n";}
	virtual void print() { cout<< "print Base\n"; }
};

struct Derived : public Base
{
	Derived() { cout<< "ctor Derived\n"; }
	~Derived() { cout <<"dtor Derived\n"; }
	Derived(const Derived&) { cout<< "cctor Derived\n"; }
	virtual void operator=(const Base&) {cout<< "= Derived\n";}
	virtual void print() { cout<< "print Derived\n"; }
};

static void SharedPtrTest1()
{
	SharedPtr<int> p1(new int(15));
	SharedPtr<int> p2(p1);

	SharedPtr<int> p3;
	p3 = p1;

	SharedPtr<Derived> d1(new Derived());
	SharedPtr<Base> b1(new Base());
	b1 = d1;

	SharedPtr<int> p5(new int (7));
	SharedPtr<const int> p4(p5);
	
}

static void SharedPtrTest2()
{
	SharedPtr<Point> p4(new Point());
	SharedPtr<Point> p5(new Point(1.5, 2));
	p5 = p4;

}

int main()
{
	SharedPtrTest1();
	SharedPtrTest2();
	return 0;
}
