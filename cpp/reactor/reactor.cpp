/*******************************
    Yonatan Zaken
    Reactor
    CPP
    ILRD - RD8081               
*******************************/

#include "reactor.hpp"

namespace ilrd
{

void Reactor::Run()
{

}

void Reactor::Stop()
{

}

void Reactor::InsertFD(int fd, FDListener::Operation service, boost::function<void(void)> func)
{
    //m_handlerMap.insert(std::pair<int, FDListener::Operation>::pair(fd, service), func);
    m_handlerMap.insert(std::make_pair(fd, service), func);
}

void Reactor::RemoveFD(int fd, FDListener::Operation service)
{

}

} // namespace ilrd


