/*************************
         SOCKET
      Header File
    Author : Yonatan Zaken
      Date : 05/04/2020          
*************************/

#ifndef ILRD_RD8081_SOCKET_SERVER_HPP
#define ILRD_RD8081_SOCKET_SERVER_HPP

#include <netdb.h> /* getaddinfo */

typedef enum Flag
{
    CLIENT,
    SERVER
} flag_t;

enum status
{
    SUCCESS,
    FAIL_SOCKET = -1,
    FAIL_SENDTO = -1,
    FAIL_RECVFROM = -1,
    FAIL_BIND = -1,
    FAIL = 1
};

void InitHints(struct addrinfo *hints, int family, int socktype, int flags);
int GetInternetAddr(struct addrinfo* res, flag_t flag);

#endif 




