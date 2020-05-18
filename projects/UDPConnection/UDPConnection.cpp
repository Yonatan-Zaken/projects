/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/

#include <iostream> // cout
#include <unistd.h> // close
#include <cstring>  // memset

extern "C"
{
    #include "socket.h"
}

#include "UDPConnection.hpp"
#include "logger.hpp"

namespace ilrd
{

UDPConnection::UDPConnection():
    m_sockfd(GetUDPSocket())
{
    std::cout << "sockfd: " << m_sockfd << "\n";
}

/*****************************************************************************/

UDPConnection::~UDPConnection()
{
    close(m_sockfd);
}

/*****************************************************************************/

void UDPConnection::SendTo(const char *buffer) const
{
    std::cout << "in send to sockfd is: " << m_sockfd << "\n";
    if (-1 == (sendto(m_sockfd, buffer, strlen(buffer), 0,
    &m_sendToAddr, m_addrLen))) 
    {
        LOG_DEBUG("sendto fail");
        //throw
    }
}

/*****************************************************************************/

void UDPConnection::ReceiveFrom(char *buffer)
{
    if (-1 == (recvfrom(m_sockfd, buffer, BLOCK_SIZE, 0, 
    &m_sendToAddr, &m_addrLen))) 
    {
        LOG_DEBUG("recvfrom fail");
        //throw
    }
    LOG_DEBUG("sasasassasasasaa");
}

/*****************************************************************************/

int UDPConnection::GetFD() const noexcept
{
    return m_sockfd;    
}

/*****************************************************************************/

int UDPConnection::GetUDPSocket()
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    struct addrinfo *servinfo = NULL;

    InitHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);    
    
    int err_val = 0;
    if (0 != (err_val = getaddrinfo(NULL, "4443", &hints, &servinfo))) 
    {
        LOG_DEBUG("getaddrinfo fail");
        //throw
    }

    int sockfd = 0;
    if (-1 == (sockfd = GetInternetAddr(servinfo, SERVER)))
    {
        LOG_DEBUG("getinternetaddr fail");
        //throw
    }

    freeaddrinfo(servinfo);

    return sockfd;
}

} // namespace ilrd


