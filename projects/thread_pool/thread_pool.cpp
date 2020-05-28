/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/
#include <algorithm> // for_each
#include <boost/make_shared.hpp> // boost::make_shared

#include <iostream>

#include "thread_pool.hpp"
#include "logger_preprocessor.hpp"

namespace ilrd
{

/********************************** Details ***********************************/


/******************************* Pair Definitions *****************************/

ThreadPool::PrioratizedTask::PrioratizedTask():
    m_task(),
    m_priority()
{
}

ThreadPool::PrioratizedTask::PrioratizedTask(task_t task, IMP_Priority priority):
    m_task(task),
    m_priority(priority)
{
}

bool ThreadPool::PrioratizedTask::operator<(const PrioratizedTask& pair) const
{
    return (m_priority < pair.m_priority);
}

/*************************** ThreadPool Definitions ***************************/

ThreadPool::ThreadPool(std::size_t numOfThreads, const seconds_t& timeout):
    m_numOfThreads(numOfThreads),
    m_runFlag(true),
    m_tasks(),
    m_pauseFlag(true),
    m_lock(),
    m_condVar(),
    m_timeOut(timeout),
    m_priority(),
    m_threads()
{
    InitMap();
    InitThreads();
}

/******************************************************************************/

ThreadPool::~ThreadPool() noexcept
{
    if (m_runFlag)
    {
        Stop();
    }
}

/******************************************************************************/

void ThreadPool::Add(task_t task, Priority priority)
{ 
    m_tasks.Push(PrioratizedTask(task, m_priority[priority]));
}

/******************************************************************************/

void ThreadPool::SetNumOfThreads(std::size_t numOfThreads)
{
    Pause();

    std::size_t current = GetNumOfThreads()
    if (current > numOfThreads)
    {
        
    }

    else if (current < numOfThreads)
    {
        
    }
    
    Start();
}

/******************************************************************************/

void ThreadPool::Start()
{
    std::cout << "notifying...\n";
    m_pauseFlag = false;
    m_condVar.notify_all(); 
}

/******************************************************************************/

void ThreadPool::Pause()
{
    m_pauseFlag = true;
}

/******************************************************************************/

void ThreadPool::Stop()
{
    try
    {
        Stop(m_timeOut);
    }
    catch(...)
    {
        LOG_WARNING("error: time out for stop exipred");
    }
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
    m_pauseFlag = true;
    
    std::size_t numOfThreads = GetNumOfThreads();
    for (std::size_t i = 0; i < numOfThreads; ++i)
    {
        std::cout << "adding dummy task\n";
        m_tasks.Push(PrioratizedTask(boost::make_shared<DummyTask>(), IMP_DUMMY));
    }
    
    for (std::size_t i = 0; i < numOfThreads; ++i)
    {
        if (!m_threads[i]->try_join_for(timeout))
        {
            throw ("join error: not all thread have joined\n");    
        }
    }
}

/******************************************************************************/

std::size_t ThreadPool::GetNumOfThreads() const
{
    return m_numOfThreads;
}

/******************************* Private Functions ****************************/

void ThreadPool::InitMap()
{
    m_priority[LOW] = IMP_LOW;
    m_priority[MEDIUM] = IMP_MEDIUM;
    m_priority[HIGH] = IMP_HIGH;
}

/******************************************************************************/

void ThreadPool::InitThreads()
{
    std::size_t numOfThreads = GetNumOfThreads();
    for (size_t i = 0; i < numOfThreads; ++i)
    {
        m_threads.push_back(boost::make_shared<boost::thread>(&ThreadPool::ThreadFunc, this));
    }
}

/******************************************************************************/

void ThreadPool::ThreadFunc()
{    
    std::cout << boost::this_thread::get_id() << "\n";
    
    while (m_runFlag)
    {
        Wait();
        Execution();
    }
    std::cout << "stop func worked\n";
}

/******************************************************************************/

void ThreadPool::Wait()
{
    boost::unique_lock<boost::mutex> lock(m_lock);
    while (m_pauseFlag)
    {
        std::cout << "wait cond_var\n";
        m_condVar.wait(lock); 
    }
    lock.unlock();
    std::cout << boost::this_thread::get_id() << "out of cond_var\n";    
}

/******************************************************************************/

void ThreadPool::Execution()
{
    PrioratizedTask task;

    while (!m_pauseFlag)
    {
        m_tasks.Pop(task);
        LOG_DEBUG("pop task from queue");
        try
        {
            task.m_task->Run();
        }

        catch(...)
        {
            LOG_WARNING("task failed in ThreadFunc()");
        }
    }
}

/******************************************************************************/

} // namespace ilrd


