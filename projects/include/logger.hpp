/*******************************
    Yonatan Zaken
    Logger
    CPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_LOGGER_HPP
#define ILRD_RD8081_LOGGER_HPP

#include <queue>                   // queue
#include <fstream>                 //ofstream
#include "singleton.hpp"
#include "waitqueue.hpp"
#include "utility.hpp"

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
    std::ofstream m_file;
    boost::thread m_thread;
    Level m_level;
    WaitableQueue< std::queue <std::string> > m_queue;
    
    template<typename Logger>
    friend class Singleton;
    
    explicit Logger();	
    void ThreadFunc();
    Level GetLevel() const noexcept;

};

} // namespace ilrd

#endif
