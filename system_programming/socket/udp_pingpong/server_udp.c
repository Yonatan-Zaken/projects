#define _POSIX_C_SOURCE 200112L
#include <stdio.h>          /* printf      */
#include <unistd.h>         /* close       */
#include <string.h>         /* memcpy      */
#include <netdb.h>          /* getaddrinfo */

#include "socket.h"

#define MYPORT "4443"  
#define MAXBUFLEN 100

static int CommunicateWithServer(int sockfd);

/******************************************************************************/

int main(void)
{
    int sockfd = 0;
    int status = 0;
    struct addrinfo hints = {0};
    struct addrinfo *servinfo = NULL;
    int rv = 0;

    InitHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);    
    
    if (0 != (rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo))) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return FAIL;
    }

    if (-1 == (sockfd = GetInternetAddr(servinfo, SERVER)))
    {
        return sockfd;        
    }

    freeaddrinfo(servinfo);
    printf("server: waiting to recvfrom...\n");
    
    if (-1 == (status = CommunicateWithServer(sockfd)))
    {
        close(sockfd);
        return status;
    }
    
    close(sockfd);

    return 0;
}

/******************************************************************************/

static int CommunicateWithServer(int sockfd)
{
    struct sockaddr_storage their_addr = {0};
    socklen_t addr_len;
    char buf[MAXBUFLEN] = {0};
    char pong[5] = "pong";
    
    printf("udp server fd: %d\n", sockfd);    

    addr_len = sizeof(their_addr);
    while (1)
    {
        if (-1 == (recvfrom(sockfd, buf, MAXBUFLEN - 1 , 0, 
        (struct sockaddr *)&their_addr, &addr_len))) 
        {
            perror("recvfrom");
            return FAIL_RECVFROM;
        }

        printf("server: %s\n", buf);
        
        if (-1 == (sendto(sockfd, pong, strlen(pong), 0, 
        (struct sockaddr *)&their_addr, addr_len))) 
        {
            perror("talker: sendto");
            return FAIL_SENDTO;
        }
    }
    
    return SUCCESS;    
}
