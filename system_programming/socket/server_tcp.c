#include <stdio.h>          /* printf      */
#include <stdlib.h>         /* exit        */
#include <unistd.h>         /* close       */
#include <errno.h>          /* perror      */
#include <string.h>         /* memcpy      */
#include <sys/types.h>      /* ssize_t     */
#include <sys/socket.h>     /* socket      */
#include <netdb.h>          /* getaddrinfo */
#include <arpa/inet.h>      /* inet_ntop   */
#include <sys/wait.h>       /* wait        */

#define PORT "3490"
#define BACKLOG 10 
#define MAXDATASIZE 100 

enum status
{
    SUCCESS,
    FAIL_SOCKET = -1,
    FAIL_SEND = -1,
    FAIL_RECV = -1,
    FAIL_BIND = -1,
    FAIL_SETSOCKOPT = -1,
    FAIL_LISTEN = -1,
    FAIL_ACCEPT = -1,
    FAIL = 1
};
/********************************* Static Funcs *******************************/
static void InitHints(struct addrinfo *hints);
static int SearchIntAddr(int sockfd, struct addrinfo* res);
static int CommunicateWithServer(int sockfd);
/******************************************************************************/

static void InitHints(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
}

/******************************************************************************/

static int SearchInternetAddr(struct addrinfo* node)
{
    struct addrinfo *p = NULL;
    int sockfd = 0;
    int yes = 1;
    
    // loop through all the results and bind to the first we can
    for(p = node; p != NULL; p = p->ai_next) 
    {
        if (-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))) 
        {
            perror("server: socket");
            sockfd = FAIL_SOCKET;
            continue;
        }
        
        if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) 
        {
            perror("setsockopt");
            sockfd = FAIL_SETSOCKOPT;
            return sockfd;
        }
        
        if (-1 == bind(sockfd, p->ai_addr, p->ai_addrlen)) 
        {
            close(sockfd);
            perror("server: bind");
            sockfd = FAIL_BIND;
            continue;
        }
        
        break;
    }
    
    if (NULL == p) 
    {
        fprintf(stderr, "server: failed to bind\n");
        sockfd = FAIL_BIND;
    }
    
    return sockfd;
}

/******************************************************************************/

static int ListenForConnections(int sockfd)
{
    int new_fd = 0;
    struct sockaddr_storage their_addr; 
    socklen_t addr_len;
        
    if (-1 == listen(sockfd, BACKLOG)) 
    {
        perror("listen");
        new_fd = FAIL_LISTEN;
        return new_fd;
    }
    
    printf("server: waiting for connections...\n");    
    addr_len = sizeof(their_addr);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_len);
    if (-1 == new_fd) 
    {
        perror("accept");
        new_fd = FAIL_ACCEPT;
        return new_fd;
    }
    
    return new_fd;
}

/******************************************************************************/

static int CommunicateWithServer(int new_fd)
{
    char buf[MAXDATASIZE] = {0};
    char pong[5] = "pong";
    
    while (1)
    {
        if (-1 == (recv(new_fd, buf, MAXDATASIZE - 1, 0)))
        {
            perror("recv");
            return FAIL_RECV;    
        }
        
        printf("server: %s\n", buf);
        
        if (-1 == send(new_fd, pong, strlen(pong), 0))
        {
            perror("send");
            return FAIL_SEND;    
        }    
    }
}

/******************************************************************************/

int main(void)
{
    int sockfd = 0;
    int new_fd = 0; 
    int status = 0;
    struct addrinfo hints = {0};
    struct addrinfo *servinfo = NULL;
    int rv = 0;
    
    InitHints(&hints);
    
    if (0 != (rv = getaddrinfo(NULL, PORT, &hints, &servinfo))) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
   
   if (-1 == (sockfd = SearchInternetAddr(servinfo)))
    {
        return sockfd;        
    }
   
    freeaddrinfo(servinfo); 
     
    if(-1 == (new_fd = ListenForConnections(sockfd)))
    {
        close(sockfd);
        return new_fd;
    }
      
    if (!fork()) 
    { 
        close(sockfd); 
        if (-1 == (status = CommunicateWithServer(new_fd)))
        {
            close(new_fd);
            return status;   
        }
    }
    
    close(new_fd); 
    close(sockfd);
    wait(NULL);
    
    return 0;
}
    
    
    
