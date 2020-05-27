/*******************************
    Yonatan Zaken
    Wait Queue
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_WAITQUEUE_HPP
#define ILRD_RD8081_WAITQUEUE_HPP

#include <semaphore.h>      // semaphore_t
#include <boost/chrono.hpp> // nanoseconds
#include <boost/thread/mutex.hpp>   // boost::scoped_lock

#include <iostream>

#include "utility.hpp"

namespace ilrd
{
// Q needs to have a default constructor.
//class Q should have push, pop, isempty, front, value_type
template <class Q> 
class WaitableQueue: private Uncopyable
{

typedef boost::chrono::nanoseconds nanoseconds_t;
typedef boost::chrono::seconds seconds_t;

public:
    explicit WaitableQueue();
    ~WaitableQueue() noexcept;

    void Push(const typename Q::value_type& data);
    void Pop(typename Q::reference dest); 
    bool Pop(typename Q::reference dest, const nanoseconds_t &timeout);
    bool IsEmpty() const;
    
private:
    Q m_queue;
    sem_t m_counter;
    mutable boost::mutex m_lock;

    std::size_t GetSemCount();
    bool SemTimedWait(const nanoseconds_t& timeout);
    void SafePop(typename Q::value_type &data);
};

/**************************** exception details *******************************/

namespace details
{

class SemwaitError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("sem_wait() error");
    }
};

class SempostError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("sem_post() error");
    }
};

class SemgetvalueError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("sem_getvalue() error");
    }
};

class SemtimedwaitError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("sem_timewait() error");
    }
};

class SeminitError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("sem_init() error");
    }
};

} // namespace details

/************************ WaitableQueue definitions **************************/

template <class Q> 
WaitableQueue<Q>::WaitableQueue()
{
    if (-1 == sem_init(&m_counter, 0, 0))
    {
        throw details::SeminitError();
    }
}

/*****************************************************************************/

template <class Q> 
WaitableQueue<Q>::~WaitableQueue() noexcept
{
    sem_destroy(&m_counter);
}

/*****************************************************************************/

template <class Q> 
void WaitableQueue<Q>::Push(const typename Q::value_type& data)
{
    boost::mutex::scoped_lock scopedLock(m_lock);
    m_queue.push(data);
   
    if (-1 == sem_post(&m_counter))
    {
        throw details::SempostError();
    }
}

/*****************************************************************************/

template <class Q> 
void WaitableQueue<Q>::Pop(typename Q::reference data)
{
    if (-1 == sem_wait(&m_counter))
    {
        throw details::SemwaitError();
    }
    
    SafePop(data);
}

/*****************************************************************************/

template <class Q>
bool WaitableQueue<Q>::Pop(typename Q::reference data, const nanoseconds_t& timeout)
{
    if (false == SemTimedWait(timeout))
    {
        return false;
    }
    
    SafePop(data);

    return true;
}

/*****************************************************************************/

template <class Q>
bool WaitableQueue<Q>::IsEmpty() const
{
    boost::mutex::scoped_lock scopedLock(m_lock);
    bool isEmpty = m_queue.empty();   

    return isEmpty;
}

/**************************** Priavate Methods ***************************/

template <class Q>
bool WaitableQueue<Q>::SemTimedWait(const nanoseconds_t& timeout)
{
    seconds_t secondsExpire = boost::chrono::duration_cast<seconds_t>(timeout);
    nanoseconds_t nanoExpire = timeout - secondsExpire;

    struct timespec expirationTime;
    memset(&expirationTime, 0, sizeof(timespec));

    expirationTime.tv_sec = time(nullptr) + secondsExpire.count();
    expirationTime.tv_nsec = nanoExpire.count();

    if (-1 == sem_timedwait(&m_counter, &expirationTime))
    {
        if (ETIMEDOUT == errno)
        {
            return false;
        }
        
        throw details::SemtimedwaitError();
    }

    return true;
}

/*****************************************************************************/

template <class Q>
void WaitableQueue<Q>::SafePop(typename Q::value_type& data)
{
    boost::mutex::scoped_lock scopedLock(m_lock);
    data = m_queue.front();
    m_queue.pop();
}

} // namespace ilrd

#endif
