/*******************************
    Yonatan Zaken
    UDPClient
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_UDPCLIENT_HPP
#define ILRD_RD8081_UDPCLIENT_HPP

#include <inttypes.h>   // uintn_t
#include <sys/socket.h> // struct sockaddr

#include "utility.hpp"

namespace ilrd
{

class UDPClient 
{
public:	
    explicit UDPClient(const char *port);		
    ~UDPClient() noexcept;
    //UDPClient(const UDPClient& other); = default
    //UDPClient& operator=(const UDPClient& rhs); = default

    void SendTo(const uint8_t *buffer) const;
    void ReceiveFrom(uint8_t *buffer);
    int GetFD() const noexcept;

    class UDPClientError: public std::runtime_error
    {
    public:
        explicit UDPClientError(const char *message);
    };

private:
    struct addrinfo *m_serverInfo;
    int m_sockfd;

    int GetUDPSocket(const char* port);
};

} // namespace ilrd


#endif
