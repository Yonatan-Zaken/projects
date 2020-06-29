/*******************************
    Yonatan Zaken
    Framework
    CPP
    ILRD - RD8081               
*******************************/

#include "framework.hpp"

namespace ilrd
{

Framework::Framework(ConfigurationBase *config):
    m_config(config), 
    m_reactor(),
    m_threadpool(GetNumThreads(), GetThreadpoolTimeout()),
    m_dirmonitor(m_reactor, GetPath().c_str()),
    m_storage(new HeapStorage(GetStoragePath())),
    m_scheduler(m_reactor),
    m_servicelocator()
{
    Add("reactor", &m_reactor);
    Add("threadpool", &m_threadpool);
    Add("dirmonitor", &m_dirmonitor);
    Add<boost::shared_ptr<Storage> >("storage", m_storage);
    Add("scheduler", &m_scheduler);
    Add("servicelovator", &m_servicelocator);
}

/******************************************************************************/

void Framework::Start()
{
    m_reactor.Run();
}

/******************************************************************************/

void Framework::Stop()
{
    m_reactor.Stop();
}

/**************************** Private Definitions *****************************/

std::string Framework::GetPath()
{
    std::string path(m_config->Get("ILRD_DIRMONITOR_PATH").c_str());
    return path;
}

/******************************************************************************/

int Framework::GetNumThreads()
{
    return atoi(m_config->Get("ILRD_NUM_OF_THREADS").c_str());
}

/******************************************************************************/

Framework::seconds_t Framework::GetThreadpoolTimeout()
{
    Framework::seconds_t timeOut(atoi(m_config->Get("ILRD_THREADPOOL_TIMEOUT").c_str()));
    return timeOut;
}

/******************************************************************************/

uint64_t Framework::GetNumOf4KBlocks()
{
    return static_cast<uint64_t>(atoi(m_config->Get("ILRD_NUMBER_OF_4K_BLOCKS").c_str()));
}

/******************************************************************************/

std::string Framework::GetStoragePath()
{
    std::string path(m_config->Get("ILRD_STORAGE_PATH").c_str());
    return path;
}

} // namespace ilrd

