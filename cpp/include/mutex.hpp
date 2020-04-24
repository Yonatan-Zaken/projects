/*******************************
    Yonatan Zaken
    File Name
    File Type
    ILRD - RD8081               
*******************************/
#include <pthread.h>

#include "utility.hpp"

namespace ilrd
{

class Mutex: private Uncopyable
{

public:
    explicit Mutex(pthread_mutex_t& lock);	
    ~Mutex(); 
	void MutexLock();
	void MutexUnlock();
private:
    pthread_mutex_t m_lock;
};

Mutex::Mutex(pthread_mutex_t& lock): m_lock(lock)
{
    if (0!= pthread_mutex_init(&m_lock, NULL))
    {
        throw("mutex_init fail\n");
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_lock);
}

void Mutex::MutexLock()
{
	if (0 != pthread_mutex_lock(&m_lock))
	{
		throw("mutex_lock fail\n");
	}	
}

void Mutex::MutexUnlock()
{
	if (0 != pthread_mutex_unlock(&m_lock))
	{
		throw("mutex_unlock fail\n");
	}
}

} // namespace ilrd

