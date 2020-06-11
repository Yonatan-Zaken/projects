/*******************************
    Yonatan Zaken
    UDPServer
    CPP
    ILRD - RD8081               
*******************************/
#include <iostream> // cout
#include <unistd.h> // close
#include <cstring>  // memset

#include "socket.h"
#include "UDPServer.hpp"
#include "protocol_consts.hpp"

namespace ilrd
{

UDPServer::UDPServer(const char* port):
    m_sockfd(GetUDPSocket(port))
{
}

/******************************************************************************/

UDPServer::~UDPServer() noexcept
{
    close(m_sockfd);
}

/******************************************************************************/

void UDPServer::SendTo(const uint8_t *buffer) const
{
    uint64_t replySize = (buffer[protocol::OPERATION_TYPE_OFFSET] == 0) ? protocol::REPLY_READ_SIZE : protocol::REPLY_WRITE_SIZE;
    
    if (-1 == (sendto(m_sockfd, buffer, replySize, 0,
    &m_sendToAddr, m_addrLen))) 
    {
        throw details::SendtoError();
    }
}

/******************************************************************************/

void UDPServer::ReceiveFrom(uint8_t *buffer)
{
    m_addrLen = sizeof(m_sendToAddr);

    if (-1 == (recvfrom(m_sockfd, buffer, protocol::RECV_BLOCK_SIZE, 0, 
    &m_sendToAddr, &m_addrLen))) 
    {
        throw details::RecvfromError();
    }
}

/******************************************************************************/

int UDPServer::GetFD() const noexcept
{
    return m_sockfd;    
}

/******************************************************************************/

int UDPServer::GetUDPSocket(const char *port)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));

    InitHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);    
    
    struct addrinfo *servinfo = NULL;
    if (0 != getaddrinfo(NULL, port, &hints, &servinfo)) 
    {
        throw details::GetaddrinfoError();
    }

    int sockfd = 0;
    if (-1 == (sockfd = GetInternetAddr(servinfo, SERVER)))
    {
        throw details::GetInternetAddressError();
    }

    freeaddrinfo(servinfo);

    return sockfd;
}

} // namespace ilrd


