/*******************************
    Yonatan Zaken
    UDPConnection
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_UDPConnection_HPP
#define ILRD_RD8081_UDPConnection_HPP

#include <iosfwd>
#include <sys/socket.h>

#include "utility.hpp"

namespace ilrd
{

class UDPConnection: private Uncopyable
{
public:	
    explicit UDPConnection(const char* port);		
    ~UDPConnection();
    void SendTo();
    void ReceiveFrom();

    static const std::size_t BLOCK_SIZE = 4096;

private:
    int m_sockfd;
    const char* m_port;
    struct sockaddr m_sendToAddr;
    socklen_t m_addrLen;

    int GetUDPSocket();
};

} // namespace ilrd


#endif
