/*******************************
    Yonatan Zaken
    Event Queue
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_EVENTQUEUE_HPP
#define ILRD_RD8081_EVENTQUEUE_HPP

#include <queue>

#include "reactor.hpp"

namespace ilrd
{

template <class OPERATION>
class EventQueue
{
public:	
    typedef boost::function<void(void)> callback_t;

    explicit EventQueue(Reactor& reactor, int fd, callback_t callback);	
    //EventQueue(const EventQueue& other) = default;	
    //EventQueue& operator=(const EventQueue& other) = default;	
    ~EventQueue() noexcept;

    void Enqueue(OPERATION message);
    void Dequeue();

private:
    std::queue<OPERATION> m_queue;
    Reactor& m_reactor;
    int m_fd;
};

/******************************** Event Queue *********************************/

template <class OPERATION>
EventQueue<OPERATION>::EventQueue(Reactor& reactor, int fd, callback_t callback):
    m_queue(),
    m_reactor(reactor),
    m_fd(fd)
{
    m_reactor.InsertFD(fd, FDListener::WRITE, callback);
}

/******************************************************************************/

template <class OPERATION>
EventQueue<OPERATION>::~EventQueue() noexcept
{
    m_reactor.RemoveFD(m_fd, FDListener::WRITE);
}

/******************************************************************************/

template <class OPERATION>
void EventQueue<OPERATION>::Enqueue(OPERATION message)
{
    m_queue.push(message);
}

/******************************************************************************/

template <class OPERATION>
void EventQueue<OPERATION>::Dequeue()
{
    m_queue.pop();
}

} // namespace ilrd


#endif
