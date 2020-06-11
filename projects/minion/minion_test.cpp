#include <iostream>

#include "minion.hpp"
#include "utility.hpp"

using namespace ilrd;

int main()
{
	boost::shared_ptr<HeapStorage> storage(new HeapStorage(20));
	Minion minion(storage, "4443");

	minion.MinionStart();

	return 0;
}
