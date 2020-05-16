/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/
#include "connection.hpp"

namespace ilrd
{

Connection::Connection(Reactor& reactor):
    m_reactor(reactor),
    m_fd(m_udp.GetFD())
{
}

Connection::~Connection()
{
}

int Connection::GetFD() const noexcept
{
    return m_fd;
}

void Connection::Receive()
{
    m_reactor.Run();
}

void Connection::CallBack()
{
    m_udp.ReceiveFrom();
}

} // namespace ilrd


