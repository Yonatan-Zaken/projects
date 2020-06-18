#include <iostream>
#include <cstdio>

#include "master.hpp"
#include "config.hpp"
using namespace ilrd;

int main()
{
	/*
	Master m("/dev/nbd0", 4000, "4443");
	m.StartNBDCommunication();
	*/

	Config c1;
	setenv("ILRD_NUM_OF_THREADS", "4", 0);
	setenv("ILRD_THREADPOOL_TIMEOUT", "3", 0);
	setenv("ILRD_NUM_OF_MINIONS", "8", 0);
	setenv("ILRD_MINION_IP", "10.1.0.34", 0);
	setenv("ILRD_MINION_PORT", "4443", 0);
	setenv("ILRD_DIRMONITOR_PATH", "/home/student/dir1", 0);
	setenv("ILRD_NUMBER_OF_4K_BLOCKS", "4000", 0);
	setenv("ILRD_NBD_PATH", "/dev/nbd0", 1);
	setenv("ILRD_LOGGER_FILE_PATH", "/home/student/git/projects/logger/logger.txt", 1);
	setenv("ILRD_LOGGER_LEVEL", "DEBUG", 1);

	Master m1(&c1);
	m1.StartNBDCommunication();

	return 0;
}
