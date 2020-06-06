#include <iostream>
#include <cstdio>

#include "master.hpp"
using namespace ilrd;

int main()
{
	Master m("/dev/nbd0", 4096, 4096);
	

	return 0;
}
