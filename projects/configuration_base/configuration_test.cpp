#include <iostream>
#include <cstdio>
#include <cstdlib>  // getenv

#include "config.hpp"
using namespace ilrd;

int main()
{
	Config c1;
	setenv("ILRD_NUM_OF_THREADS", "4", 0);
	setenv("ILRD_NUM_OF_MINIONS", "8", 0);
	setenv("ILRD_MINION_IP", "10.1.0.34", 0);
	setenv("ILRD_MINION_PORT", "4443", 0);

	RUN_TEST(c1.Get("ILRD_NUM_OF_THREADS") == "4", "num of threads");
	RUN_TEST(c1.Get("ILRD_NUM_OF_MINIONS") == "8", "num of minions");
	RUN_TEST(c1.Get("ILRD_MINION_IP") == "10.1.0.34", "minion id");
	RUN_TEST(c1.Get("ILRD_MINION_PORT") == "4443", "minion port");

	return 0;
}
