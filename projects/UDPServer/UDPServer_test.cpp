#include <iostream>

#include "UDPConnection.hpp"
#include "utility.hpp"

using namespace ilrd;

int main()
{
	char buffer[20] = {0};
	UDPConnection udp;
	char buffer2[20] = "haha\0";

	for (size_t i = 0; i < 4; i++)
	{
		udp.ReceiveFrom(buffer);
		std::cout << buffer << "\n";
		udp.SendTo(buffer2);
	}
	
	return 0;
}
