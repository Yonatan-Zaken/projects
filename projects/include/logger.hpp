/*******************************
    Yonatan Zaken
    LOGGER
    HPP
    05/05/20
    ILRD - RD8081               
*******************************/

#define NAN      0
#define ERROR    1
#define WARNING  2
#define INFO     3
#define DEBUG    4

#if ((LOG_LEVEL > DEBUG) || (LOG_LEVEL < NAN))
#error Invalid Log Level
#else 
#ifndef LOG_ERROR
#define LOG_ERROR(X) {std::cerr << "ERROR [" << X << "] " << __FILE__ << " " <<\
__LINE__ <<"\n";}
#endif
#ifndef LOG_WARNING
#define LOG_WARNING(X) {std::cerr << "WARNING [" << X << "] " << __FILE__ <<\
 " " << __LINE__ <<"\n";}
#endif
#ifndef LOG_INFO
#define LOG_INFO(X) {std::cerr << "INFO [" << X << "] " << __FILE__ << " " <<\
__LINE__ <<"\n";}
#endif
#ifndef LOG_DEBUG
#define LOG_DEBUG(X) {std::cerr << "DEBUG [" << X << "] " << __FILE__ << " " <<\
__LINE__ <<"\n";}
#endif
#endif

#if (LOG_LEVEL == INFO) // Info
    #undef LOG_DEBUG
    #define LOG_DEBUG(X) {} 

#elif (LOG_LEVEL == WARNING) // Warning
    #undef LOG_INFO
    #define LOG_INFO(X) {}
    #undef LOG_DEBUG
    #define LOG_DEBUG(X) {}

#elif (LOG_LEVEL == ERROR) // Error
    #undef LOG_WARNING
    #define LOG_WARNING(X) {}
    #undef LOG_INFO
    #define LOG_INFO(X) {}
    #undef LOG_DEBUG
    #define LOG_DEBUG(X) {}

#elif (LOG_LEVEL == NAN)   // NAN
    #undef LOG_ERROR
    #define LOG_ERROR(X) {}
    #undef LOG_WARNING
    #define LOG_WARNING(X) {}
    #undef LOG_INFO
    #define LOG_INFO(X) {}
    #undef LOG_DEBUG
    #define LOG_DEBUG(X) {}
#endif

