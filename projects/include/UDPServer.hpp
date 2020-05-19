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

private:
    int m_sockfd;
    struct sockaddr m_sendToAddr;
    socklen_t m_addrLen;
    int GetUDPSocket(const char* port);
};

namespace details
{

class GetaddrinfoError: public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return ("getaddrinfo error");
    }
};

class GetInternetAddressError: public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return ("GetInternetAddress error");
    }
};

class SendtoError: public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return ("sendto error");
    }
};

class RecvfromError: public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return ("revcfrom error");
    }
};

} // namespace details

} // namespace ilrd


#endif
