#include <iostream>

#include "config.hpp"
#include "dlopener.hpp"

using namespace ilrd;

int main()
{
	Config c1;
	setenv("ILRD_NUM_OF_THREADS", "4", 0);
	setenv("ILRD_THREADPOOL_TIMEOUT", "3", 0);
	setenv("ILRD_NUM_OF_MINIONS", "8", 0);
	setenv("ILRD_MINION_IP", "10.1.0.34", 0);
	setenv("ILRD_MINION_PORT", "4443", 0);
	setenv("ILRD_DIRMONITOR_PATH", "/home/student/git/projects/dlopener/plugins/", 0);
	setenv("ILRD_NUMBER_OF_4K_BLOCKS", "4000", 0);

	Framework f1(&c1);
	DLOpener dl("/home/student/git/projects/dlopener/plugins/", f1);

	f1.Start();

	return 0;
}
