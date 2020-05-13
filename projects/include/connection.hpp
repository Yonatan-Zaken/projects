/*******************************
    Yonatan Zaken
    Connection
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_CONNECTION_HPP
#define ILRD_RD8081_CONNECTION_HPP

#include "reactor.hpp"
#include "UDPConnection.hpp"
#include "utility.hpp"

namespace ilrd
{

class Connection: private Uncopyable
{
public:	
    explicit Connection(Reactor& reactor); // insert FD to reactor
    ~Connection(); // stop the reactor
    //Connection(const connection& other); = disabled	
    //Connection& operator=(const connection& other); = disabled

    void GetData();

    void Receive(); // run the reactor
    void Reply();   // create message object and send master
    int GetFd() const noexcept;

private:
    UDPConnection m_udp;
    Reactor& m_reactor;
    int m_fd_connect;
};

} // namespace ilrd

#endif
