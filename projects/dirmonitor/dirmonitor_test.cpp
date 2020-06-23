#include <iostream>
#include <cstdio>

#include "dirmonitor.hpp"
#include "dispatcher.hpp"
#include "utility.hpp"

using namespace ilrd;

int global = 0;

void Update(InotifyEvent event)
{
	std::cout << "event name: " << event.name << "\n";
	std::cout << "detected operation: " << event.operation << "\n";
}

void Death()
{

}

static void DirMonitorTest()
{
	Reactor r1;

	DirMonitor d1(r1, "/home/student/dir1");
	Observer<InotifyEvent> o1(&d1, Update, Death);
	r1.Run();

}

int main()
{
	DirMonitorTest();
	return 0;
}
