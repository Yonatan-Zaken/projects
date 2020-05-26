/*******************************
    Yonatan Zaken
    Priority Queue
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_PRIORITY_QUEUE_HPP
#define ILRD_RD8081_PRIORITY_QUEUE_HPP

#include <queue>    // priority_queue
#include <vector>   // vector

#include "utility.hpp"

namespace ilrd
{

//Requirements: T must be comparable
template <class T>
class PriorityQueue: private std::priority_queue<T>
{
public:	
    // explicit PriorityQueue(); = default
    // ~PriorityQueue(); = default
    // PriorityQueue(const PriorityQueue&) = disabled
    // PriorityQueue& operator=(const PriorityQueue&) = disabled
    
    using std::priority_queue<T>::pop;
    using std::priority_queue<T>::push;
    using std::priority_queue<T>::empty;
    
    typedef typename std::priority_queue<T>::value_type value_type;
    typedef typename std::priority_queue<T>::reference reference;
    typedef typename std::priority_queue<T>::const_reference const_reference;

    const_reference front() const;
};

template <class T>
typename PriorityQueue<T>::const_reference PriorityQueue<T>::front() const
{
    return this->top();
}

} // namespace ilrd

#endif
