/*******************************
    Yonatan Zaken
    UDPServer
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_UDPSERVER_HPP
#define ILRD_RD8081_UDPSERVER_HPP

#include <inttypes.h>   // uintn_t
#include <sys/socket.h> // struct sockaddr

#include "utility.hpp"

namespace ilrd
{

class UDPServer 
{
public:	
    explicit UDPServer(const char *port);		
    ~UDPServer() noexcept;
    //UDPServer(const UDPServer& other); = default
    //UDPServer& operator=(const UDPServer& rhs); = default

    void SendTo(const uint8_t *buffer) const;
    void ReceiveFrom(uint8_t *buffer);
    int GetFD() const noexcept;

    static const uint64_t RECV_BLOCK_SIZE = 4113;
    static const uint64_t BLOCK_SIZE = 4096;
    static const uint64_t WRITE_REPLY_SIZE = 2 * sizeof(uint8_t) + sizeof(uint64_t);
    static const uint64_t READ_REPLY_SIZE = BLOCK_SIZE + WRITE_REPLY_SIZE;
    
private:
    int m_sockfd;
    struct sockaddr m_sendToAddr;
    socklen_t m_addrLen;
    int GetUDPSocket(const char* port);
};

} // namespace ilrd


#endif
