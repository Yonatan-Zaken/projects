#include <iostream>

#include "config.hpp"
#include "framework.hpp"

using namespace ilrd;

int main()
{
	Config c1;
	setenv("ILRD_NUM_OF_THREADS", "4", 0);
	setenv("ILRD_THREADPOOL_TIMEOUT", "3", 0);
	setenv("ILRD_NUM_OF_MINIONS", "8", 0);
	setenv("ILRD_MINION_IP", "10.1.0.34", 0);
	setenv("ILRD_MINION_PORT", "4443", 0);
	setenv("ILRD_DIRMONITOR_PATH", "/home/student/dir1", 0);
	setenv("ILRD_NUMBER_OF_4K_BLOCKS", "4000", 0);

	Framework f1(&c1);

	Reactor* r1 = f1.Get<Reactor*>("reactor");
	boost::shared_ptr<Storage> s1(f1.Get<boost::shared_ptr<Storage> >("storage"));

	return 0;
}
