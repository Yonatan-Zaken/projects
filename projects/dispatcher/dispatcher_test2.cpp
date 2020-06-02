#include <iostream>

#include "dispatcher.hpp"
using namespace ilrd;

class Testing: public ObserverBase<int>
{
public:
	explicit Testing(Dispatcher<ObserverBase<int>, int> *dispatcher);
	virtual void Update();
	virtual void UpdateDeath();
};


int main()
{
	Dispatcher<Testing, int> d1; 

	return 0;
}
