#include <iostream>

#include "UDPConnection.hpp"
#include "utility.hpp"

using namespace ilrd;

int main()
{
	char buffer[20] = {0};
	UDPConnection udp;
	char buffer2[20] = "haha";

	for (size_t i = 0; i < 4; i++)
	{
		udp.ReceiveFrom(buffer);
		udp.SendTo(buffer2);
	}
	
	return 0;
}
