/*************************
         SOCKET
      Header File
    Author : Yonatan Zaken
      Date : 05/04/2020          
*************************/

#ifndef ILRD_RD8081_SOCKET_SERVER_HPP
#define ILRD_RD8081_SOCKET_SERVER_HPP

#include <netdb.h> /* getaddinfo */

typedef enum Host
{
    CLIENT,
    SERVER
} host_t;

typedef enum Protocol
{
    TCP,
    UDP
} protocol_t;

enum status
{
    FAIL_SOCKET = -1,
    FAIL_SENDTO = -1,
    FAIL_RECVFROM = -1,
    FAIL_BIND = -1,
    FAIL_CONNECT = -1
};

void InitHints(struct addrinfo *hints, int family, int socktype, int flags);
int GetSocket(char *hostname, const char *port,struct addrinfo *hints, 
protocol_t prot, host_t host);
int UDPDataTransfer(int sockfd);
int TCPDataTransfer(int sockfd, fd_set *master);
void CloseConnection(int num_of_bytes, int index, fd_set *master);

#endif 




