#include <iostream>
#include <cstdio>

#include "master.hpp"
using namespace ilrd;

int main()
{
	Master m("/dev/nbd0", 4000, "4443");
	m.StartNBDCommunication();

	return 0;
}
