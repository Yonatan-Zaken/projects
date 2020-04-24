#include <iostream> 
#include <pthread.h>
#include <unistd.h>

#include "utility.hpp"
#include "scopeguard.hpp"
#include "mutex.hpp"
#include "watchdog.hpp"

using namespace std;
using namespace ilrd;

int main()
{
	pthread_mutex_t lock;
	Mutex m(lock);
	Watchdog wd;
    time_t sleep_delay = 100;

	ScopeGuard<Mutex, &Mutex::MutexLock, &Mutex::MutexUnlock> sg(m);
	{
		
		
	}
	
	ScopeGuard<Watchdog, &Watchdog::Start, &Watchdog::Stop> sg2(wd);
	{
		while (sleep_delay)
   		{
        	sleep_delay = sleep(sleep_delay);
    	}
	}

	return 0;
}