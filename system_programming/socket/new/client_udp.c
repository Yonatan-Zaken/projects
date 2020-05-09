#define _POSIX_C_SOURCE 200112L
#include <stdio.h>          /* printf      */
#include <unistd.h>         /* close       */
#include <string.h>         /* memcpy      */
#include <netdb.h>          /* getaddrinfo */

#include "socket.h"

#define SERVERPORT "4443"   
#define MAXBUFLEN 100

static int CommunicateWithServer(int sockfd, struct addrinfo* res);

/******************************************************************************/

int main(int argc, char *argv[])
{
    int sockfd = 0;
    struct addrinfo hints = {0};
    struct addrinfo *res = NULL;
    int rv = 0;

    if (argc != 2) 
    {
        fprintf(stderr,"usage: talker hostname message\n");
        return FAIL;
    }

    InitHints(&hints, AF_INET, SOCK_DGRAM, 0);    
    
    if (0 != (rv = getaddrinfo(argv[1], SERVERPORT, &hints, &res)))
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return FAIL;
    }
    
    if (FAIL_SOCKET == (sockfd = GetInternetAddr(res, CLIENT)))
    {
        return FAIL;        
    }
    
    if (FAIL_RECVFROM == CommunicateWithServer(sockfd, res))
    {
        close(sockfd);
        return FAIL;
    }  
    
    freeaddrinfo(res);
    close(sockfd);
    
    return 0;
}

/******************************************************************************/

static int CommunicateWithServer(int sockfd, struct addrinfo* res)
{
    char ping[5] = "ping";
    char buf[MAXBUFLEN] = {0};
    char msg_to_send[30] = {0};

    while (1)
    {
        fgets(msg_to_send, sizeof(msg_to_send), stdin);
        msg_to_send[strlen(msg_to_send) - 1] = '\0';

        if (0 == strcmp(msg_to_send, "quit"))
        {
            break;
        }

        if (-1 == (sendto(sockfd, msg_to_send, strlen(msg_to_send), 0, 
        res->ai_addr, res->ai_addrlen))) 
        {
            perror("talker: sendto");
            return FAIL;
        }
        
        if (-1 == (recvfrom(sockfd, buf, MAXBUFLEN - 1 , 0,
        res->ai_addr, &res->ai_addrlen))) 
        {
            perror("recvfrom");
            return FAIL;
        }
        
        printf("udp client get packet from server: %s\n", buf);
    }

    return 0;
}
