#include <iostream>
#include <boost/bind.hpp>
#include <cstdio>
#include "dispatcher.hpp"
#include "utility.hpp"

using namespace ilrd;

int value = 0;

void UpdateFunc(int)
{
	++value;
}

void SpecialUpdateFunc(Observer<int> *observer)
{
	--value;
	delete observer;
}

void DeathFunc()
{
	--value;
}

static void DispatcherTest1()
{
	{
	Dispatcher<ObserverBase<int>, int> *d1 = new Dispatcher<ObserverBase<int>, int>;

	Observer<int> o1(d1, UpdateFunc, DeathFunc);
	Observer<int> o2(d1, UpdateFunc, DeathFunc);
	Observer<int> o3(d1, UpdateFunc, DeathFunc);
	Observer<int> o4(d1, UpdateFunc, DeathFunc);
	
	d1->Broadcast(2);

	RUN_TEST(4 == value, "update func");

	Observer<int> *o5 = new Observer<int>(d1, boost::bind(SpecialUpdateFunc, o5), DeathFunc);

	d1->Broadcast(2);

	RUN_TEST(7 == value, "update func");

	delete d1;
	}
	std::cout << "value: " << value << "\n";
	RUN_TEST(0 == value, "update func");
}

int main()
{
	DispatcherTest1(); 

	return 0;
}
