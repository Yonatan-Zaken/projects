/*******************************
    Yonatan Zaken
    UDPClient
    CPP
    ILRD - RD8081               
*******************************/
#include <iostream> // cout
#include <unistd.h> // close
#include <cstring>  // memset

#include "socket.h"
#include "UDPClient.hpp"
#include "protocol_consts.hpp"

namespace ilrd
{

UDPClient::UDPClient(const char* port):
    m_sockfd(GetUDPSocket(port))
{
}

/******************************************************************************/

UDPClient::~UDPClient() noexcept
{
    close(m_sockfd);
}

/******************************************************************************/

void UDPClient::SendTo(const uint8_t *buffer) const
{
    uint64_t replySize = (buffer[protocol::OPERATION_TYPE_OFFSET] == 0) ? protocol::REPLY_READ_SIZE : protocol::REPLY_WRITE_SIZE;
    
    if (-1 == (sendto(m_sockfd, buffer, replySize, 0,
    &m_sendToAddr, m_addrLen))) 
    {
        throw UDPClientError("sendto error");
    }
}

/******************************************************************************/

void UDPClient::ReceiveFrom(uint8_t *buffer)
{
    m_addrLen = sizeof(m_sendToAddr);

    if (-1 == (recvfrom(m_sockfd, buffer, protocol::RECV_BLOCK_SIZE, 0, 
    &m_sendToAddr, &m_addrLen))) 
    {
        throw UDPClientError("revcfrom error");
    }
}

/******************************************************************************/

int UDPClient::GetFD() const noexcept
{
    return m_sockfd;    
}

/******************************************************************************/

int UDPClient::GetUDPSocket(const char *port)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));

    InitHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);    
    
    struct addrinfo *servinfo = NULL;
    if (0 != getaddrinfo("10.1.0.34", port, &hints, &servinfo)) 
    {
        throw UDPClientError("getaddrinfo error");
    }

    int sockfd = 0;
    if (-1 == (sockfd = GetInternetAddr(servinfo, CLIENT)))
    {
        throw UDPClientError("GetInternetAddress error");
    }

    freeaddrinfo(servinfo);

    return sockfd;
}

/******************************************************************************/

UDPClient::UDPClientError::UDPClientError(const char *message):
    std::runtime_error(message)
{
}

} // namespace ilrd

