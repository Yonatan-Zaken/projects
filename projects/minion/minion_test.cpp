#include <iostream>

#include "minion.hpp"
#include "utility.hpp"

using namespace ilrd;

int main()
{

	boost::shared_ptr<HeapStorage> storage(new HeapStorage(4));
	Minion minion(storage);

	minion.MinionStart();

	return 0;
}
