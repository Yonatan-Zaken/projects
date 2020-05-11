/*******************************
    Yonatan Zaken
    Scheduler
    CPP
    ILRD - RD8081               
*******************************/
#include <boost/bind.hpp> // bind

#include "scheduler.hpp"

namespace ilrd
{

Scheduler::Scheduler(Reactor& reactor):
    m_timer(reactor, boost::bind(&Scheduler::Callback, this))
{
}

/***********************************************************************/

void Scheduler::AddTask(task_func_t taskFunc, nanoseconds expirationTime, nanoseconds interval)
{
    m_timer.Arm(expirationTime);
    m_tasks.push(Task(taskFunc, time_point(expirationTime) , interval));
}

/***********************************************************************/

void Scheduler::Clear()
{
    while (!m_tasks.empty())
    {
        m_tasks.pop();
    }
}

/***********************************************************************/

void Scheduler::Callback()
{
    Scheduler::Task topTask(m_tasks.top().m_taskFunc, m_tasks.top().m_runTime, m_tasks.top().m_interval);

    m_tasks.top().m_taskFunc();
    m_tasks.pop();

    if (0 != topTask.m_interval.count())
    {
        //?????????????
        topTask.m_runTime = boost::chrono::system_clock::now() + topTask.m_interval;
        m_tasks.push(topTask);
    }
    
    if (m_tasks.empty())
    {
        m_timer.Disarm();
    }

    else
    {
        m_timer.Arm(boost::chrono::system_clock::now() + 
        m_tasks.top().m_interval);
    }
 
}

/***********************************************************************/

Scheduler::Task::Task(task_func_t taskFunc, time_point runTime, 
nanoseconds interval):
    m_taskFunc(taskFunc),
    m_runTime(runTime),
    m_interval(interval)
{
}

/***********************************************************************/

bool Scheduler::Task::operator<(const Scheduler::Task& rhs) const
{
    //return (time_point(m_interval) > rhs.m_runTime);
    return (m_runTime > rhs.m_runTime);
}

} // namespace ilrd




