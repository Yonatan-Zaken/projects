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
    InitThreads(GetNumOfThreads());
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
    std::size_t current = GetNumOfThreads();
    if (current < numOfThreads)
    {
        AddThreads(numOfThreads - current);
    }

    else if (current > numOfThreads)
    {
        RemoveThreads(current - numOfThreads);
    }

    m_numOfThreads = numOfThreads;
}

/******************************************************************************/

void ThreadPool::Start()
{
    boost::unique_lock<boost::mutex> lock(m_lock);
    m_pauseFlag = false;
    lock.unlock();
    m_condVar.notify_all(); 
}

/******************************************************************************/

void ThreadPool::Pause()
{
    m_pauseFlag = true;
    AddDummys();
}

/******************************************************************************/

void ThreadPool::Stop()
{
    Stop(m_timeOut);
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
    
    AddDummys();
    Start();
    JoinThreads(timeout);    
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

void ThreadPool::InitThreads(std::size_t toAdd)
{
    for (size_t i = 0; i < toAdd; ++i)
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
    std::cout << boost::this_thread::get_id() << "stop func worked\n";
}

/******************************************************************************/

void ThreadPool::Wait()
{
    if (m_pauseFlag)
    {
        boost::unique_lock<boost::mutex> lock(m_lock);
        while (m_pauseFlag)
        {
            m_condVar.wait(lock); 
        }
        lock.unlock();
        std::cout << boost::this_thread::get_id() << "out of cond_var\n";    
    }
}

/******************************************************************************/

void ThreadPool::Execution()
{
    PrioratizedTask task;

    m_tasks.Pop(task);
    LOG_DEBUG("pop task from queue");
    try
    {
        task.m_task->Run();
    }

    catch(details::RemoveThreadExcept& e)
    {
        boost::unique_lock<boost::mutex> lock(m_lock);
        DetachThread();
        lock.unlock();
        return;
    }

    catch(...)
    {
        LOG_WARNING("task failed in ThreadFunc()");
    }
}

/******************************************************************************/

void ThreadPool::JoinThreads(const ThreadPool::seconds_t& timeout)
{
    std::vector<thread_t>::iterator it;
    for (it = m_threads.begin(); it != m_threads.end(); ++it)
    {
        std::cout << "joining " << ((*it).get())->get_id() << "\n";
        if (!(((*it).get())->try_join_for(timeout)))
        {
            LOG_WARNING("error: time out for stop exipred");
            throw details::JoinTimeoutError();    
        }
        
    }
    
/*
    std::size_t numOfThreads = GetNumOfThreads();
    for (std::size_t i = 0; i < numOfThreads; ++i)
    {
        if (!m_threads[i]->try_join_for(timeout))
        {
            LOG_WARNING("error: time out for stop exipred");
            throw details::JoinTimeoutError();    
        }
    }
*/
}

/******************************************************************************/

void ThreadPool::AddDummys()
{
    std::size_t numOfThreads = GetNumOfThreads();
    for (std::size_t i = 0; i < numOfThreads; ++i)
    {
        m_tasks.Push(PrioratizedTask(boost::make_shared<DummyTask>(), IMP_SPECIAL));
    }
}

/******************************************************************************/

void ThreadPool::AddThreads(std::size_t toAdd)
{
    InitThreads(toAdd);    
}

/******************************************************************************/

void ThreadPool::DetachThread()
{
    std::vector<thread_t>::iterator it;
    for (it = m_threads.begin(); ((*it).get())->get_id() != boost::this_thread::get_id(); ++it)
    {
    }
    
    std::cout << "detaching " << ((*it).get())->get_id() << "\n";
    ((*it).get())->detach();
    m_threads.erase(it);
}

/******************************************************************************/

void ThreadPool::RemoveThreadTask::Run()
{
    throw details::RemoveThreadExcept();
}

void ThreadPool::RemoveThreads(std::size_t toRemove)
{
    for (std::size_t i = 0; i < toRemove; ++i)
    {
        m_tasks.Push(PrioratizedTask(boost::make_shared<RemoveThreadTask>(), IMP_SPECIAL));
    }
}

/******************************************************************************/

} // namespace ilrd


