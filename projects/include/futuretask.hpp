/*********************
    Future Task
    Header File
    27/05/2020
    ILRD - RD8081               
*********************/

#ifndef ILRD_RD8081_FUTURE_TASK_HPP
#define ILRD_RD8081_FUTURE_TASK_HPP

#include "thread_pool.hpp" // Task

namespace ilrd
{

template <class VALUE>
// VALUE must be dufault contructable, copy constructable, and copy assignable
class FutureTask: public ThreadPool::Task
{
public:
    explicit FutureTask();
    // virtual ~FutureTask() noexcept = default;

    virtual VALUE TaskFunc() = 0;
    // TaskFunc must beimplemented with the function the task should do

    void Run(); 
    bool IsFinished() const;
    VALUE GetValue();
    VALUE Wait();

private:
    VALUE m_value;
    bool m_isFinished;
    boost::mutex m_lock;
    boost::condition_variable m_condVar;
};

/******************************************************************************/

FutureTask<VALUE>::FutureTask():
    m_value(),
    m_isFinished(false)
{
}

/******************************************************************************/

void FutureTask<VALUE>::Run()
{
    m_value = TaskFunc();
    m_isFinished = true;
    m_condVar.notify_one();
}

/******************************************************************************/

VALUE FutureTask<VALUE>::GetValue()
{
    return m_value;
}

/******************************************************************************/

VALUE FutureTask<VALUE>::Wait()
{
    boost::unique_lock<boost::mutex> lock(m_lock);
    while (!IsFinished())
    {
        m_condVar.wait(lock); 
    }
    lock.unlock();

    return GetValue();
}

/******************************************************************************/

bool FutureTask<VALUE>::IsFinished()
{
    return m_isFinished;
}

} // namespace ilrd

#endif // ILRD_RD8081_FUTURE_TASK_HPP

