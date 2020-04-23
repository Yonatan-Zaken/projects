#include <iostream> 
#include <pthread.h>

#include "utility.hpp"
#include "scopeguard.hpp"
#include "mutex.hpp"

using namespace std;
using namespace ilrd;

int main()
{
	pthread_mutex_t lock;
	Mutex m(lock);

	ScopeGuard<Mutex, &Mutex::MutexLock, &Mutex::MutexUnlock> sg(m);
	{
		
	}
	
	return 0;
}