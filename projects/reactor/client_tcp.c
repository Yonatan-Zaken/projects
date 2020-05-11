#define _POSIX_C_SOURCE 200112L
#include <stdio.h>          /* printf      */
#include <unistd.h>         /* close       */
#include <errno.h>          /* perror      */
#include <string.h>         /* memcpy      */
#include <sys/socket.h>     /* socket      */
#include <netdb.h>          /* getaddrinfo */

#include "socket.h"

#define PORT "4443" 
#define MAXDATASIZE 100 

enum status
{
    SUCCESS,
    FAIL_SOCKET = -1,
    FAIL_CONNECT = -1,
    FAIL_SETSOCKOPT = -1,
    FAIL_LISTEN = -1,
    FAIL_ACCEPT = -1,
    FAIL_SEND = -1,
    FAIL_RECV = -1,
    FAIL = 1
};

/******************************************************************************/
/*
static void InitHints(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
}
*/
/******************************************************************************/
/*
static int GetInternetAddr(struct addrinfo* node)
{
    struct addrinfo *runner = NULL;
    int sockfd = 0;
    
    for(runner = node; NULL != runner; runner = runner->ai_next) 
    {
        if (-1 == (sockfd = socket(runner->ai_family, runner->ai_socktype, 
        runner->ai_protocol))) 
        {
            perror("client: socket");
            sockfd = FAIL_SOCKET;
            continue;
        }
        
        if (-1 == connect(sockfd, runner->ai_addr, runner->ai_addrlen)) 
        {
            close(sockfd);
            perror("client: connect");
            sockfd = FAIL_CONNECT;
            continue;
        }
        
        break;
    }

    if (NULL == runner)
    {
        fprintf(stderr, "talker: failed to create socket\n");
        return sockfd;
    }
    
    return sockfd;
}
*/
/******************************************************************************/

static int CommunicateWithServer(int new_fd)
{
    char buf[MAXDATASIZE] = {0};
    char msg_to_send[30] = {0};
    
    while (1)
    {
        fgets(msg_to_send, sizeof(msg_to_send), stdin);
        msg_to_send[strlen(msg_to_send) - 1] = '\0';

        if (0 == strcmp(msg_to_send, "quit"))
        {
            break;
        }

        if (-1 == send(new_fd, msg_to_send, strlen(msg_to_send), 0))
        {
            perror("send");
            return FAIL_SEND;    
        }    
        
        if (-1 == (recv(new_fd, buf, MAXDATASIZE - 1, 0)))
        {
            perror("recv");
            return FAIL_RECV;    
        }

        buf[MAXDATASIZE] = '\0';
        
        printf("tcp client get packet from server: %s\n", buf);
        
    }
    
    return SUCCESS;
}

/******************************************************************************/

int main(int argc, char *argv[])
{
    int sockfd = 0;
    int status = 0;
    int rv = 0;
    struct addrinfo hints = {0};
    struct addrinfo *servinfo = NULL;
    
    if (argc != 2) 
    {
        fprintf(stderr,"usage: client hostname\n");
        return FAIL;
    }
    
    InitHints(&hints);
    /*
    if (0 != (rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)))
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    */
    
    sockfd = GetSocket(argv[1], AF_INET, SOCK_STREAM, 0);
    /*
    if (FAIL_SOCKET == (sockfd = GetInternetAddr(servinfo)))
    {
        return sockfd;
    }
    
    freeaddrinfo(servinfo);
    */
    
    if (FAIL_SEND == (status = CommunicateWithServer(sockfd)))
    {
        close(sockfd);
        return status;
    }
        
    close(sockfd);
    
    return 0;
}

