#ifndef ILRD_RD8081_QUEUE_HPP
#define ILRD_RD8081_QUEUE_HPP

#include <boost/chrono.hpp> // nanoseconds 
#include <queue>
#include <pthread.h> // semaphore_t

namespace ilrd
{
// Q needs to have a default constructor.
template <class Q> 
//class Q should have push, pop, isempty, front, value_type
class WaitableQueue
{

typedef boost::chrono::nanoseconds nanoseconds_t;

public:
    void Push(const Q::value_type &data);
    void Pop(Q::value_type &dest); 
    bool Pop(Q::value_type &dest, const nanoseconds_t &timeout); //timeout
    bool IsEmpty()const;//noexcept ??
    
private:
    Q m_queue;
    // semaphore pthread/interprocess ?
};

template <class Q> 
void WaitableQueue::Push(const Q::value_type &data)
{

}

template <class Q> 
void WaitableQueue::Pop(Q::value_type &data)
{

}

template <class Q>
void WaitableQueue::Pop(Q::value_type &data, nanoseconds_t& timeout)
{

}

template <class Q>
bool IsEmpty() const // noexcept??
{

}

} // namespace ilrd

#endif
