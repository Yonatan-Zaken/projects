#include <iostream>
#include <cstdio>

#include <boost/shared_ptr.hpp>

#include "storage.hpp"

using namespace ilrd;

int main()
{
	char buffer[4096] = {0};
	boost::shared_ptr<Storage> h1(new HeapStorage(3));

	h1->Write("hello", 2);
	h1->Read(buffer, 2);

	std::cout << buffer << "\n";

	return 0;
}
