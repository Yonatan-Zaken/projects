/*******************************
    Yonatan Zaken
    Connection
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_CONNECTION_HPP
#define ILRD_RD8081_CONNECTION_HPP

#include <boost/shared_ptr.hpp>

#include "reactor.hpp"
#include "UDPServer.hpp"
#include "message.hpp"
#include "utility.hpp"
#include "eventqueue.hpp"

namespace ilrd
{

class Connection: private Uncopyable
{
public:	
    typedef boost::function <void(void)> callback_t;
    
    explicit Connection(const char* port, Reactor& reactor, callback_t callback); 
    ~Connection() noexcept; 
    //Connection(const connection& other); = disabled	
    //Connection& operator=(const connection& other); = disabled

    int GetFD() const noexcept;
    boost::shared_ptr<RequestMessage> ConstructRequest();
    void SendMessage(boost::shared_ptr<ReplyMessage> reply);

private:
    UDPServer m_udp;
    Reactor& m_reactor;
    callback_t m_callback;
    //EventQueue<boost::shared_ptr<ReplyMessage> > m_eventqueue;
};

} // namespace ilrd

#endif
