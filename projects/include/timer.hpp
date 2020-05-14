/*******************************
    Yonatan Zaken
    Timer
    HPP
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_TIMER_HPP
#define ILRD_RD8081_TIMER_HPP

#include <sys/timerfd.h> // itimerspec
#include <boost/chrono.hpp> // time_point

#include "reactor.hpp"
#include "utility.hpp" // Uncopyable

namespace ilrd
{

class TimerFD: private Uncopyable
{
public:
    typedef boost::function<void(void)> callback_t;
    typedef boost::chrono::system_clock::time_point time_point;
    typedef boost::chrono::nanoseconds nanoseconds;
    typedef boost::chrono::seconds seconds;

    explicit TimerFD(Reactor& reactor, callback_t callback);
    ~TimerFD() noexcept;
    //TimerFD(const timer& other) = default
    //TimerFD& operator=(const timer& other) = default

    void Arm(time_point runTime);
    void Arm(nanoseconds runDelay);
    void Disarm();

    class TimerException: public std::exception
    {
    public:
        explicit TimerException(int errno_val);
        const char *what() const noexcept;
    private:
        int m_errno;
    };

private:
    int timed_fd;
    Reactor& m_reactor;
    callback_t m_schedulerCallBack;
    int TimerFDCreate();
    void CallBack();
    void SetTime(struct itimerspec* timer);
};

} // namespace ilrd

#endif // ILRD_RD8081_TIMER_HPP

// CLOCK_BOOTTIME

