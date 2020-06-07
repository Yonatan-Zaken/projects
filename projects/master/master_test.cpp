#include <iostream>
#include <cstdio>

#include "master.hpp"
using namespace ilrd;

int main()
{
	Master m("/dev/nbd0", 128 * 1024 * 1024, 128 * 1024 * 1024);
	m.StartNBDCommunication();

	return 0;
}
