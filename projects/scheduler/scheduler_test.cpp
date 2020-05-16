#include <iostream>
#include <boost/bind.hpp>

#include "scheduler.hpp"

using namespace ilrd;

typedef boost::chrono::seconds seconds;

void Print1()
{
	std::cout << "first task\n";
}

void Print2(int val)
{
	std::cout << "secon task val: " << val << "\n";
}

static void SchedTest1()
{
	Reactor r1;
	Scheduler s1(r1);
	s1.AddTask(Print1, seconds(6),seconds(2));

	int val = 5;
	s1.AddTask(boost::bind(Print2, val) ,seconds(4), seconds(10));
	/*s1.AddTask(boost::bind(&Scheduler::Clear, &s1), seconds(4), seconds(0));*/
	s1.AddTask(boost::bind(&Reactor::Stop, &r1), seconds(15), seconds(0));
	
	r1.Run();
}

int main()
{
	SchedTest1();

	return 0;
}
