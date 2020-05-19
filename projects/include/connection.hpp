/*******************************
    Yonatan Zaken
    Connection
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_CONNECTION_HPP
#define ILRD_RD8081_CONNECTION_HPP

#include <boost/shared_ptr.hpp>

#include "utility.hpp"
#include "UDPServer.hpp"
#include "message.hpp"

namespace ilrd
{

class Connection: private Uncopyable
{
public:	
    explicit Connection(const char* port); 
    //~Connection(); = default
    //Connection(const connection& other); = disabled	
    //Connection& operator=(const connection& other); = disabled

    int GetFD() const noexcept;
    boost::shared_ptr<Message> ConstructRequest();
    void SendMessage(boost::shared_ptr<Message> reply);

    static const uint64_t RECV_BLOCK_SIZE = 4113;
    static const uint64_t DATA_BLOCK_SIZE = 4096;
    static const uint64_t REPLY_READ_SIZE = 4106;

private:
    UDPServer m_udp;
};

} // namespace ilrd

#endif
