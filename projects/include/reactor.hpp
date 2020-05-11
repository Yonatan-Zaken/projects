/*******************************
    Yonatan Zaken
    Reactor
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_REACTOR_HPP
#define ILRD_RD8081_REACTOR_HPP

#include <map>            
#include <boost/function.hpp>

#include "utility.hpp"
#include "fdlistner.hpp"

namespace ilrd
{

class Reactor: private Uncopyable
{
public:
    //Reactor() = default
    //~Reactor() = default
    //Reactor(const Reactor&) = disabled
    //Reactor& operator=(const Reactor&) = disabled

    typedef boost::function<void(void)> callback_t;
    typedef std::map<FDListener::key_t, callback_t> map_t;

    void Run();
    void Stop();
    void InsertFD(int fd, FDListener::Operation service, 
    callback_t callback);
    void RemoveFD(int fd, FDListener::Operation service);
    
private:
    FDListener m_monitor;
    map_t m_handlerMap;
    int m_stopFlag;
};

} // namespace ilrd

#endif
