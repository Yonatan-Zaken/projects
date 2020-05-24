/*******************************
    Yonatan Zaken
    Logger
    CPP
    ILRD - RD8081               
*******************************/

#include <cstdlib>  // getenv
#include <boost/chrono.hpp> // seconds
#include <boost/bind.hpp> // boost::bind

#include "logger.hpp"

namespace ilrd
{

/********************************** Details ***********************************/

namespace details
{

class GetEnvError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("invalid value in ENV variable");
    }
};

class OpenLogFileError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("ofstream fail to open log file");
    }
};

} // namespace details

/**************************** LogFile Definitions *****************************/

Logger::LogFile::LogFile(const char *logPath):
    m_file(logPath, std::ofstream::out | std::ofstream::app)
{   
    if (m_file.fail())
    {
        throw details::OpenLogFileError();
    }
}

/**************************** Logger Definitions ******************************/

Logger::Logger():
    m_logger(GetEnv("ILRD_LOGGER_FILE_PATH")),
    m_level(GetLevel("ILRD_LOGGER_LEVEL")),
    m_queue(),
    m_runFlag(true),
    m_thread(boost::bind(&Logger::ThreadFunc, this))
{
}

/******************************************************************************/

Logger::~Logger() noexcept
{
    m_runFlag = false;
    m_thread.join();
}

/******************************************************************************/

void Logger::Log(const std::string& message, Level level)
{
    if (level <= m_level)
    {
        m_queue.Push(message);
    }
}

/******************************* Private Functions ****************************/

void Logger::ThreadFunc()
{
    while (m_runFlag || (!m_queue.IsEmpty()))
    {
        WriteToLog();
    }
}

/******************************************************************************/

const char *Logger::GetEnv(const char *envVal) const
{
    const char *env = std::getenv(envVal);
    if (nullptr == env)
    {
        throw details::GetEnvError();
    }

    return env;
}

/******************************************************************************/

Logger::Level Logger::GetLevel(const char *logLevel) const 
{
    std::string envLevel(GetEnv(logLevel));

    if ("NONE" == envLevel)
    {
        return Logger::NONE;
    }
    
    else if ("ERROR" == envLevel)
    {
        return Logger::ERROR;
    }
    
    else if ("WARNING" == envLevel)
    {
        return Logger::WARNING;
    }

    else if ("INFO" == envLevel)
    {
        return Logger::INFO;
    }

    else if("DEBUG" == envLevel)
    {
        return Logger::DEBUG;
    }

    throw details::GetEnvError();  
}

/******************************************************************************/

void Logger::WriteToLog() 
{
    std::string messageToWrite;

    if (m_queue.Pop(messageToWrite, boost::chrono::seconds(1)))
    {
        m_logger.m_file << messageToWrite;
    }
}

} // namespace ilrd

