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
    m_serverInfo(),
    m_sockfd(GetUDPSocket(port))    
{
}

/******************************************************************************/

UDPClient::~UDPClient() noexcept
{
    freeaddrinfo(m_serverInfo);
    close(m_sockfd);
}

/******************************************************************************/

void UDPClient::SendTo(const uint8_t *buffer) const
{
    uint64_t replySize = (buffer[protocol::OPERATION_TYPE_OFFSET] == 0) ? protocol::REPLY_READ_SIZE : protocol::REPLY_WRITE_SIZE;
    
    if (-1 == (sendto(m_sockfd, buffer, replySize, 0,
    m_serverInfo->ai_addr, m_serverInfo->ai_addrlen))) 
    {
        throw UDPClientError("sendto error");
    }
}

/******************************************************************************/

void UDPClient::ReceiveFrom(uint8_t *buffer)
{
    int bytes_read = 0;
    if (-1 == (bytes_read = recvfrom(m_sockfd, buffer, protocol::REPLY_READ_SIZE, 0, 
    m_serverInfo->ai_addr, &(m_serverInfo->ai_addrlen)))) 
    {
        throw UDPClientError("revcfrom error");
    }

    std::cout << "bytes read udp client: " << bytes_read << "\n";
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
    
    if (0 != getaddrinfo("10.1.0.34", port, &hints, &m_serverInfo)) 
    {
        throw UDPClientError("getaddrinfo error");
    }

    int sockfd = 0;
    if (-1 == (sockfd = GetInternetAddr(m_serverInfo, CLIENT)))
    {
        throw UDPClientError("GetInternetAddress error");
    }

    return sockfd;
}

/******************************************************************************/

UDPClient::UDPClientError::UDPClientError(const char *message):
    std::runtime_error(message)
{
}

} // namespace ilrd

