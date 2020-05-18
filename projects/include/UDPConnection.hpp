/*******************************
    Yonatan Zaken
    UDPConnection
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_UDPConnection_HPP
#define ILRD_RD8081_UDPConnection_HPP

#include <inttypes.h>   // uintn_t
#include <sys/socket.h> // struct sockaddr

#include "utility.hpp"

namespace ilrd
{

class UDPConnection: private Uncopyable
{
public:	
    explicit UDPConnection();		
    ~UDPConnection();
    void SendTo(const char *buffer) const;
    void ReceiveFrom(char *buffer);
    int GetFD() const noexcept;

    static const uint64_t BLOCK_SIZE = 4096;
    static const uint64_t READ_REPLY_SIZE = 4106;
    static const uint64_t WRITE_REPLY_SIZE = 2 * sizeof(uint8_t) + sizeof(uint64_t);

private:
    int m_sockfd;
    struct sockaddr m_sendToAddr;
    socklen_t m_addrLen;
    int GetUDPSocket();
};

} // namespace ilrd


#endif
