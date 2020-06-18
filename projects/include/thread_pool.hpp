/*********************
    Thread Pool
    Header File
    26/05/2020
    ILRD - RD8081               
*********************/
#ifndef ILRD_RD8081_THREADPOOL_HPP
#define ILRD_RD8081_THREADPOOL_HPP

#include <vector>   // std::vector
#include <queue>    // std::queue
#include <map>      // std::map
#include <exception>    //std::exception
#include <boost/thread.hpp> // boost::thread
#include <boost/chrono.hpp> // seconds
#include <boost/shared_ptr.hpp>
#include <boost/atomic.hpp>

#include "utility.hpp"  // Uncopyable
#include "waitqueue.hpp"
#include "priority_queue.hpp"

namespace ilrd
{

namespace details
{

class JoinTimeoutError: public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return ("error: fail to join all threads until timeout");
    }
};

struct  RemoveThreadExcept: public std::exception
{
};

} // namespace details

class ThreadPool: private Uncopyable
{
public:
    class Task;
    typedef boost::chrono::seconds seconds_t;
    typedef boost::shared_ptr<Task> task_t;

    enum Priority
    {
        LOW,
        MEDIUM,
        HIGH
    };

    class Task
    {
    public:
        //explicit Task() = default;
        virtual ~Task() noexcept
        {
        }
        //Task(const Task&) = default;
        //Task& operator=(const Task&) = default;
        
        virtual void Run() = 0;
    };

    explicit ThreadPool(std::size_t numOfThreads, const seconds_t& timeout);
    ~ThreadPool() noexcept;
    // ThreadPool(const ThreadPool& other) = disabled;
    //ThreadPool& operator=(const ThreadPool& rhs) = disabled; 

    void Add(task_t task, Priority priority);
    void SetNumOfThreads(std::size_t numOfThreads);
    void Start();
    void Pause();
    void Stop();
    void Stop(const seconds_t& timeout);
    std::size_t GetNumOfThreads() const;

private:
    enum IMP_Priority
    {
        IMP_LOW,
        IMP_MEDIUM,
        IMP_HIGH,
        IMP_SPECIAL
    };

    class PrioratizedTask
    {
    public:
        explicit PrioratizedTask();
        explicit PrioratizedTask(task_t task, IMP_Priority priority);
        bool operator<(const PrioratizedTask& pair) const;
        task_t m_task;
        IMP_Priority m_priority;
    };

    class RemoveThreadTask: public ThreadPool::Task
    {
    public:
        virtual void Run();
    };

    friend class RemoveThreadTask;

    typedef WaitableQueue<PriorityQueue<PrioratizedTask> > waitqueue_t;
    typedef boost::shared_ptr<boost::thread> thread_t;

    std::size_t m_numOfThreads;
    boost::atomic<bool> m_runFlag;
    waitqueue_t m_tasks;
    bool m_pauseFlag;
    boost::mutex m_lock;
    boost::condition_variable m_condVar;
    const seconds_t m_timeOut;
    std::map<Priority, IMP_Priority> m_priority;
    std::vector<thread_t> m_threads;

    void InitMap();
    void InitThreads(std::size_t toAdd);
    void ThreadFunc();
    void Execution();
    void Wait();
    void AddDummys();
    void JoinThreads(const seconds_t& timeout);
    void AddThreads(std::size_t toAdd);
    void RemoveThreads(std::size_t toRemove);
    void DetachThread();
    static bool IsSameThread(boost::shared_ptr<boost::thread> thread);

};

} // namespace ilrd

#endif // ILRD_RD8081_THREADPOOL_HPP

