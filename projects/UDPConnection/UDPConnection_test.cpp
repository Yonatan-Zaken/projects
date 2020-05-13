#include <iostream>

#include "UDPConnection.hpp"
#include "utility.hpp"

using namespace ilrd;

int main()
{
	UDPConnection udp("4443");

	for (size_t i = 0; i < 4; i++)
	{
		udp.ReceiveFrom();
		udp.SendTo();
	}

	return 0;
}
