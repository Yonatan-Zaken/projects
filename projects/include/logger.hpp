/*******************************
    Yonatan Zaken
    Logger
    CPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_LOGGER_HPP
#define ILRD_RD8081_LOGGER_HPP

#include <boost/thread/mutex.hpp>  // boost::mutex
#include <fstream>  //ofstream
#include "singleton.hpp"
#include "utility.hpp"

namespace ilrd
{

class Logger
{
public:	
    enum Level
    {
        NUN,
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        NUM_OF_LEVELS
    };

    explicit Logger();	
    ~Logger() noexcept;
    // Logger(const Logger& other);	
    // Logger& operator=(const Logger& other); 	

    void Log(const std::string&, Level level);
    
    void Error(const std::string&);
    void Warning(const std::string&);
    void Info(const std::string&);
    void Debug(const std::string&);

private:
    std::ofstream m_file;
    boost::mutex m_lock;
};

// FILE *f = Singleton<FILE>::GetInstance();

} // namespace ilrd


#endif
