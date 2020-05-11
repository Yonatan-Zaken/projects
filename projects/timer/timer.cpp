/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/

#include <cstring>  // memeset
#include <cerrno>   // errno
#include <sys/timerfd.h> // timerfd_create
#include <boost/bind.hpp> // bind
#include <iostream>

#include "timer.hpp"

namespace ilrd
{

TimerFD::TimerFD(Reactor& reactor, callback_t callback):
    timed_fd(TimerFDCreate()),
    m_reactor(reactor),
    m_callback(boost::bind(&TimerFD::CallBack, this)),
    m_schedulerCallBack(callback)
{
    m_reactor.InsertFD(timed_fd, FDListener::READ, m_callback);
}

TimerFD::~TimerFD() noexcept
{
    m_reactor.RemoveFD(timed_fd, FDListener::READ);
    close(timed_fd);
}

void TimerFD::Arm(time_point expirationTime)
{
    nanoseconds duration = expirationTime - boost::chrono::system_clock::now();

    seconds expirSeconds = boost::chrono::duration_cast<seconds>(duration);

    nanoseconds expirNano = duration - expirSeconds;

    struct itimerspec newRunTime;
    memset(&newRunTime, 0, sizeof(itimerspec));
    
    newRunTime.it_value.tv_sec = expirSeconds.count();
    newRunTime.it_value.tv_nsec = expirNano.count();

    if(-1 == timerfd_settime(timed_fd, 0, &newRunTime, nullptr))
    {
        //throw(errno)
    }
}

void TimerFD::Arm(nanoseconds expirationTime)
{
    boost::chrono::system_clock::time_point time = expirationTime + boost::chrono::system_clock::now();

    Arm(time);
}

void TimerFD::Disarm()
{
    struct itimerspec to_disarm;
    
    memset(&to_disarm, 0, sizeof(itimerspec));
    if(-1 == timerfd_settime(timed_fd, 0, &to_disarm, nullptr))
    {
        //throw(errno)
    }
}

void TimerFD::CallBack()
{
    char buf[1] = {0};
    read(timed_fd, buf, strlen(buf));

    m_schedulerCallBack();
}

int TimerFD::TimerFDCreate()
{
    int fd = 0;

    if(-1 == (fd = timerfd_create(CLOCK_BOOTTIME, 0)))
    {
        //throw(errno)
    }

    return fd;
}

} //namespace ilrd
