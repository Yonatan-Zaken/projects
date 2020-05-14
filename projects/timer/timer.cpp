/*******************************
    Yonatan Zaken
    Timer
    CPP
    ILRD - RD8081               
*******************************/

#include <cstring>  // memeset
#include <cerrno>   // errno
#include <boost/bind.hpp> // bind
#include <sys/timerfd.h> // timerfd_create

#include "timer.hpp"

namespace ilrd
{

TimerFD::TimerFD(Reactor& reactor, callback_t callback):
    timed_fd(TimerFDCreate()),
    m_reactor(reactor),
    m_schedulerCallBack(callback)
{
    m_reactor.InsertFD(timed_fd, 
    FDListener::READ, boost::bind(&TimerFD::CallBack, this));
}

/******************************************************************************/

TimerFD::~TimerFD() noexcept
{
    close(timed_fd);
    m_reactor.RemoveFD(timed_fd, FDListener::READ);
}

/******************************************************************************/

void TimerFD::Arm(time_point expirationTime)
{
    nanoseconds duration = expirationTime - boost::chrono::system_clock::now();

    seconds expirSeconds = boost::chrono::duration_cast<seconds>(duration);

    nanoseconds expirNano = duration - expirSeconds;

    struct itimerspec newRunTime;
    memset(&newRunTime, 0, sizeof(itimerspec));
    
    newRunTime.it_value.tv_sec = expirSeconds.count();
    newRunTime.it_value.tv_nsec = (expirNano.count() <= 0) ? 1 :
    expirNano.count();

    SetTime(&newRunTime);
}

/******************************************************************************/

void TimerFD::Arm(nanoseconds expirationTime)
{
    boost::chrono::system_clock::time_point time = expirationTime + boost::chrono::system_clock::now();

    Arm(time);
}

/******************************************************************************/

void TimerFD::Disarm()
{
    struct itimerspec to_disarm;
    memset(&to_disarm, 0, sizeof(itimerspec));

    SetTime(&to_disarm);
}

/******************************************************************************/

void TimerFD::CallBack()
{
    char buf[sizeof(uint64_t)] = {0};
    if(sizeof(uint64_t) != read(timed_fd, &buf, sizeof(buf)))
    {
        throw TimerException(errno);
    }

    m_schedulerCallBack();
}

/******************************************************************************/

int TimerFD::TimerFDCreate()
{
    int fd = 0;

    if(-1 == (fd = timerfd_create(CLOCK_BOOTTIME, 0)))
    {
        throw TimerException(errno);
    }

    return fd;
}

/******************************************************************************/

void TimerFD::SetTime(struct itimerspec* timer)
{
    if (-1 == timerfd_settime(timed_fd, 0, timer, nullptr))
    {
        throw TimerException(errno);
    }
}

/**************************** Exception Definition ****************************/

TimerFD::TimerException::TimerException(int errno_val): m_errno(errno_val)
{
}

const char *TimerFD::TimerException::what() const noexcept
{
    return strerror(m_errno);
}

} //namespace ilrd
