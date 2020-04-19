#include <stdio.h>          /* printf      */
#include <stdlib.h>         /* exit        */
#include <unistd.h>         /* close       */
#include <errno.h>          /* perror      */
#include <string.h>         /* memcpy      */
#include <sys/types.h>      /* ssize_t     */
#include <sys/socket.h>     /* socket      */
#include <netdb.h>          /* getaddrinfo */
#include <arpa/inet.h>      /* inet_ntop   */

#define PORT "3490" // the port users will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once

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

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (AF_INET == sa->sa_family) 
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/******************************************************************************/

static void InitHints(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
}

/******************************************************************************/

static int GetInternetAddr(struct addrinfo* node)
{
    struct addrinfo *p = NULL;
    int sockfd = 0;
    
    for(p = node; NULL != p; p = p->ai_next) 
    {
        if (-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))) 
        {
            perror("client: socket");
            sockfd = FAIL_SOCKET;
            continue;
        }
        
        if (-1 == connect(sockfd, p->ai_addr, p->ai_addrlen)) 
        {
            close(sockfd);
            perror("client: connect");
            sockfd = FAIL_CONNECT;
            continue;
        }
        
        break;
    }

    if (NULL == p)
    {
        fprintf(stderr, "talker: failed to create socket\n");
        return sockfd;
    }
    
    return sockfd;
}

/******************************************************************************/

static int CommunicateWithServer(int new_fd)
{
    char buf[MAXDATASIZE] = {0};
    char ping[5] = "ping";
    
    while (1)
    {
        if (-1 == send(new_fd, ping, strlen(ping), 0))
        {
            perror("send");
            return FAIL_SEND;    
        }    

        printf("server: %s\n", buf);
        
        if (-1 == (recv(new_fd, buf, MAXDATASIZE - 1, 0)))
        {
            perror("recv");
            return FAIL_RECV;    
        }
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
        exit(1);
    }
    
    if (0 != (rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)))
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    if (FAIL_SOCKET == (sockfd = GetInternetAddr(servinfo)))
    {
        return sockfd;
    }
   
    freeaddrinfo(servinfo);
    
    if (FAIL_SEND == (status = CommunicateWithServer(sockfd)))
    {
        close(sockfd);
        return status;
    }
        
    close(sockfd);
    
    return 0;
}

