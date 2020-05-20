/*******************************
    Yonatan Zaken
    Priority Queue
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_PRIORITY_QUEUE_HPP
#define ILRD_RD8081_PRIORITY_QUEUE_HPP

#include <queue>    // priority_queue

#include "utility.hpp"

namespace ilrd
{

template <class T>
class PriorityQueue: private std::priority_queue<T>, private Uncopyable
{
public:	
    typedef T value_type;
    typedef T& reference;

    // explicit PriorityQueue(); = default
    // ~PriorityQueue(); = default
    // PriorityQueue(const PriorityQueue&) = disabled
    // PriorityQueue& operator=(const PriorityQueue&) = disabled
    
    using std::priority_queue<T>::pop;
    using std::priority_queue<T>::push;
    using std::priority_queue<T>::empty;
    
    reference front() const;
};

template <class T>
T& PriorityQueue<T>::front() const
{
    return top();
}

} // namespace ilrd



#endif
