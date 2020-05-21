/*******************************
    Yonatan Zaken
    Logger
    CPP
    ILRD - RD8081               
*******************************/

#include <boost/thread/scoped_thread.hpp>
#include <cstdio>
#include "logger.hpp"

namespace ilrd
{

Logger::Logger()
{
    boost::scoped_thread<> scopedThread(m_thread(ThreadFunc));
    const char *envPath = std::getenv("ILRD_LOGGER_FILE_PATH");
    
    m_file.open("ILRD_LOGGER_FILE_PATH");
}

Logger::~Logger() noexcept
{
}

void Logger::Log(const std::string& message, Level level)
{
    m_queue.Push(message);
}

void Logger::ThreadFunc()
{
    std::string messageToWrite;
    m_queue.Pop(messageToWrite);

}

Level Logger::GetLevel() const noexcept
{
    std::string envLevel(std::getenv("ILRD_LOGGER_LEVEL"));

    if (NONE == envLevel)
    {
        return NONE;
    }

    else if (ERROR == envLevel)
    {
        return ERROR;
    }
    
    else if (WARNING == envLevel)
    {
        return WARNING;
    }

    else if (INFO == envLevel)
    {
        return INFO;
    }

    else
    {
        return DEBUG;
    }
}

} // namespace ilrd

