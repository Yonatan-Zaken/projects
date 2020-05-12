/*******************************
    Yonatan Zaken
    Scheduler
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_SCHEDULER_HPP
#define ILRD_RD8081_SCHEDULER_HPP

#include <queue> // priority_queue

#include "timer.hpp" // Timer

namespace ilrd
{

class Scheduler: private Uncopyable
{
public:
    typedef boost::function<void(void)> task_func_t;
    typedef TimerFD::time_point time_point;
    typedef TimerFD::nanoseconds nanoseconds;

    explicit Scheduler(Reactor& reactor);
    //Scheduler(const Scheduler&) = default
    //Scheduler& operator=(const Scheduler&) = default
    //~Scheduler() = default

    void AddTask(task_func_t m_taskFunc, nanoseconds expirationTime, 
                 nanoseconds interval);
    void Clear();

private:
    struct Task
    {
        explicit Task(task_func_t taskFunc, time_point runTime, 
                      nanoseconds interval);

        bool operator<(const Task& rhs) const;
        
        task_func_t m_taskFunc;
        time_point m_runTime;
        nanoseconds m_interval;
    };

    void Callback();

    TimerFD m_timer;
    std::priority_queue<Task> m_tasks;
};

} // namespace ilrd

#endif // ILRD_RD8081_SCHEDULER_HPP

