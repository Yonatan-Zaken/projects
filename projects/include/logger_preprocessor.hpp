/*******************************
    Yonatan Zaken
    LOGGER
    HPP
    05/05/20
    ILRD - RD8081               
*******************************/

#include <sstream>
#include "logger.hpp"

#ifndef LOG_ERROR
#define LOG_ERROR(X) { std::ostringstream msg;\
msg << __TIME__ << " ERROR [" << X << "]. " << "FILE: " __FILE__ <<\
". LINE: " << __LINE__ << ".\n";\
ilrd::Singleton<ilrd::Logger>::GetInstance()->Log(msg.str() , ilrd::Logger::ERROR); }
#endif

#ifndef LOG_WARNING
#define LOG_WARNING(X) { std::ostringstream msg;\
msg << __TIME__ << " WARNING [" << X << "]. " << "FILE: " __FILE__ <<\
". LINE: " << __LINE__ << ".\n";\
ilrd::Singleton<ilrd::Logger>::GetInstance()->Log(msg.str() , ilrd::Logger::WARNING);}
#endif

#ifndef LOG_INFO
#define LOG_INFO(X) { std::ostringstream msg;\
msg << __TIME__ << " INFO [" << X << "]. " << "FILE: " __FILE__ <<\
". LINE: " << __LINE__ << ".\n";\
ilrd::Singleton<ilrd::Logger>::GetInstance()->Log(msg.str() , ilrd::Logger::INFO); }
#endif

#ifndef LOG_DEBUG
#define LOG_DEBUG(X) { std::ostringstream msg;\
msg << __TIME__ << " DEBUG [" << X << "]. " << "FILE: " __FILE__ <<\
". LINE: " << __LINE__ << ".\n";\
ilrd::Singleton<ilrd::Logger>::GetInstance()->Log(msg.str() , ilrd::Logger::DEBUG); }
#endif
