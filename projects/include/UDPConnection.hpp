/*******************************
    Yonatan Zaken
    UDPConnection
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_UDPConnection_HPP
#define ILRD_RD8081_UDPConnection_HPP

#include <iosfwd>
#include <sys/socket.h> // struct sockaddr

#include "utility.hpp"

namespace ilrd
{

class UDPConnection: private Uncopyable
{
public:	
    explicit UDPConnection();		
    ~UDPConnection();
    void SendTo();
    void ReceiveFrom();
    int GetFD() const noexcept;

    static const uint64_t BLOCK_SIZE = 4113;

private:
    int m_sockfd;
    struct sockaddr m_sendToAddr;
    socklen_t m_addrLen;
    int GetUDPSocket();

};

} // namespace ilrd


#endif
