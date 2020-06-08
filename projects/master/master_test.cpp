#include <iostream>
#include <cstdio>

#include "master.hpp"
using namespace ilrd;

int main()
{
	Master m("/dev/nbd0", 128 * 1024 * 1024, "4443");
	m.StartNBDCommunication();

	return 0;
}
