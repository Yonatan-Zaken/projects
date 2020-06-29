#include <iostream>

#include "utility.hpp"
#include "minion.hpp"
#include "config.hpp"

using namespace ilrd;

int main()
{
	//boost::shared_ptr<HeapStorage> storage(new HeapStorage(4000));
	Config c1;
	setenv("ILRD_NUM_OF_THREADS", "4", 0);
	setenv("ILRD_THREADPOOL_TIMEOUT", "3", 0);
	setenv("ILRD_NUM_OF_MINIONS", "8", 0);
	setenv("ILRD_MINION_IP", "10.1.0.34", 0);
	setenv("ILRD_MINION_PORT", "4443", 0);
	setenv("ILRD_DIRMONITOR_PATH", "/home/student/dir1", 0);
	setenv("ILRD_NUMBER_OF_4K_BLOCKS", "4000", 0);
	setenv("ILRD_STORAGE_PATH", "/home/student/storage/", 0);

	Minion minion(&c1);
	minion.MinionStart();

	return 0;
}