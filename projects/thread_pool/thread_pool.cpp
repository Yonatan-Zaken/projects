/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/
#include <algorithm> // for_each
#include <boost/make_shared.hpp> // boost::make_shared
#include <boost/bind.hpp> // boost::bind

#include <iostream>

#include "thread_pool.hpp"

namespace ilrd
{

/********************************** Details ***********************************/


/******************************* Pair Definitions *****************************/

ThreadPool::PrioratizedTask::PrioratizedTask(task_t task, Priority priority):
    m_task(task),
    m_priority(priority)
{
}

bool ThreadPool::PrioratizedTask::operator<(const PrioratizedTask& pair)
{
    return (m_priority < pair.m_priority);
}

/*************************** ThreadPool Definitions ***************************/

ThreadPool::ThreadPool(std::size_t numOfThreads):
    m_numOfThreads(numOfThreads),
    m_runFlag(true),
    m_tasks(),
    m_pauseFlag(true),
    m_lock(),
    m_condVar(),
    m_threads(numOfThreads, boost::make_shared<boost::thread>(&ThreadPool::ThreadFunc, this))
{
    std::cout << "ThreaPool ctor\n";
}

/******************************************************************************/

struct JoinFunctor
{
    void operator()(const boost::shared_ptr<boost::thread>& thread)
    {
        thread->join();
    }
};

ThreadPool::~ThreadPool() noexcept
{
    std::cout << "ThreaPool dtor\n";
    std::for_each(m_threads.begin(), m_threads.end(), JoinFunctor());
}

/******************************************************************************/

void ThreadPool::Add(task_t task, Priority priority)
{
    boost::shared_ptr<PrioratizedTask> priorityTask(new PrioratizedTask(task, priority));
    m_tasks.Push(priorityTask);
}

/******************************************************************************/

void ThreadPool::SetNumOfThreads(std::size_t numOfThreads)
{
    
}

/******************************************************************************/

void ThreadPool::Start()
{
    std::cout << "notifying...\n";
    
    boost::mutex::scoped_lock scopeLock(m_lock);
    m_pauseFlag = false;
    m_condVar.notify_all(); 
}

/******************************************************************************/

void ThreadPool::Pause()
{
    m_pauseFlag = true;
}

/******************************************************************************/

class DummyTask: public ThreadPool::Task
{
    virtual void Run()
    {

    }
};

void ThreadPool::Stop(const ThreadPool::seconds_t& timeout)
{
    m_runFlag = false;
    m_pauseFlag = false;
    
    boost::shared_ptr<PrioratizedTask> task;
    while (!m_tasks.IsEmpty())
    {
        m_tasks.Pop(task);
    }
    
    //std::for_each(m_threads.begin(), m_threads.end(), DummyTaskFunctor())

    for (size_t i = 0; i < m_numOfThreads; ++i)
    {
        ThreadPool::Add(boost::make_shared<DummyTask>(), ThreadPool::HIGH);
    }
}

/******************************************************************************/

std::size_t ThreadPool::GetNumOfThreads() const
{
    return m_numOfThreads;
}

/******************************* Private Functions ****************************/

void ThreadPool::ThreadFunc()
{    
    std::cout << "in the ThreadFunc()\n";
    std::cout << "m_runFlag = " << m_runFlag << "\n";
    std::cout << "m_pauseFlag = " << m_pauseFlag << "\n";
    boost::shared_ptr<PrioratizedTask> task;
    
    while (m_runFlag)
    {
        boost::mutex::scoped_lock scopeLock(m_lock);
        while (m_pauseFlag)
        {
            std::cout << "wait cond_var\n";
            m_condVar.wait(scopeLock);    
        }
        scopeLock.unlock();        

        while (!m_pauseFlag)
        {
            if (m_tasks.Pop(task, seconds_t(1)))
            {
                std::cout << "pop task\n";
                task->m_task->Run();
            }   
        }
    }
}

} // namespace ilrd


