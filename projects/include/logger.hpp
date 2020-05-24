/*******************************
    Yonatan Zaken
    Logger
    CPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_LOGGER_HPP
#define ILRD_RD8081_LOGGER_HPP

#include <queue>    // queue
#include <fstream>  // ofstream
#include <boost/thread/scoped_thread.hpp>

#include "singleton.hpp"
#include "waitqueue.hpp"
#include "utility.hpp"  // Uncopyable

// define environment variable ILRD_LOGGER_FILE_PATH
// define environment variable ILRD_LOGGER_LEVEL

namespace ilrd
{

class Logger: private Uncopyable
{
public:	
    enum Level
    {
        NONE,
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        NUM_OF_LEVELS
    };

    ~Logger() noexcept;
    // Logger(const Logger& other);	= disabled
    // Logger& operator=(const Logger& other); = disabled 	
    void Log(const std::string& message, Level level);
    
private:
    struct LogFile
    {
        explicit LogFile(const char *logPath);
        //~LogFile(); = default

        std::ofstream m_file;
    };
    
    explicit Logger();	
    friend class Singleton<Logger>;

    LogFile m_logger;
    Level m_level;
    WaitableQueue< std::queue <std::string> > m_queue;
    bool m_runFlag;
    boost::thread m_thread;
    
    void ThreadFunc();
    const char *GetEnv(const char *envVal) const;
    Level GetLevel(const char *logLevel) const;
    void WriteToLog();
};

} // namespace ilrd

#endif
