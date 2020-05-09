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

    void Run();
    void Stop();
    void InsertFD(int fd, FDListener::Operation service, 
    boost::function<void(void)> callback);
    void RemoveFD(int fd, FDListener::Operation service);
    
private:
    FDListener m_monitor;
    std::map<std::pair<int, FDListener::Operation>, 
    boost::function<void(void)> > m_handlerMap;
};

}

#endif
