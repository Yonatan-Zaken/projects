/*******************************
    Yonatan Zaken
    Framework
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_FRAMEOWRK_HPP
#define ILRD_RD8081_FRAMEWORK_HPP

#include <boost/shared_ptr.hpp>
#include <boost/chrono.hpp> //boost::chrono::nanoseconds

#include "utility.hpp"
#include "reactor.hpp"
#include "scheduler.hpp"
#include "storage.hpp"
#include "factory.hpp"
#include "thread_pool.hpp"
#include "dirmonitor.hpp"
#include "servicelocator.hpp"
#include "configuration_base.hpp"

namespace ilrd
{

class Framework: private Uncopyable
{
public:
    explicit Framework(ConfigurationBase *config);	
    //Framework(const Framework& other) = default;	
    //Framework& operator=(const Framework& other) = default;	
    //~Framework() noexcept;

    template <class T>
    void Add(std::string key, T object);

    template <class T>
    T Get(std::string key);

    void Start();
    void Stop();

private:
    typedef boost::chrono::seconds seconds_t;

    ConfigurationBase* m_config;
    Reactor m_reactor;
    ThreadPool m_threadpool;
    DirMonitor m_dirmonitor;
    boost::shared_ptr<Storage> m_storage;
    Scheduler m_scheduler;
    ServiceLocator<std::string> m_servicelocator;

    std::string GetPath();
    std::string GetStoragePath();
    int GetNumThreads();
    seconds_t GetThreadpoolTimeout();
    uint64_t GetNumOf4KBlocks();
};

/******************************************************************************/

template <class T>
void Framework::Add(std::string key, T object)
{
    m_servicelocator.Add<T>(key, object);
}

/******************************************************************************/

template <class T>
T Framework::Get(std::string key)
{
    return m_servicelocator.Get<T>(key);
}

} // namespace ilrd

#endif //ILRD_RD8081_FRAMEOWRK_HPP
