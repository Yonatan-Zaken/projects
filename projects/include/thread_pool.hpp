/*********************
    Thread Pool
    Header File
    24/05/2020
    ILRD - RD8081               
*********************/

#include <vector>   // std::vector
#include <queue>    // std::queue
#include <boost/thread.hpp> // boost::thread


#include "utility.hpp"  // Uncopyable
#include "waitqueue.hpp"
#include "task.hpp"

namespace ilrd
{

class ThreadPool: private Uncopyable
{
public:
    explicit ThreadPool(std::size_t numOfThreads);
    ~ThreadPool() noexcept;
    // ThreadPool(const ThreadPool& other) = disabled;
    //ThreadPool& operator=(const ThreadPool& rhs) = disabled; 

    void AddTask(Task& task);
    void AddThread();
    void AddThread(std::size_t numOfThreads);
    void RemoveThread();
    void Start();
    void Stop();
    void Pause();
    std::size_t GetThreadCount() const;

private:
    std::vector<boost::thread> m_threads;
    WaitableQueue<std::queue<Task&> > m_tasks;
    bool m_runFlag;
    void ThreadFunc();
};


} // namespace ilrd



