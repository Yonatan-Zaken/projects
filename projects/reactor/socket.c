/*************************
         SOCKET
         C File
    Author : Yonatan Zaken
      Date : 05/04/2020          
*************************/
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>          /* stderr      */
#include <string.h>         /* memset      */
#include <unistd.h>         /* close       */
#include <errno.h>          /* perror      */
#include <sys/socket.h>     /* socket      */
#include <netdb.h>          /* getaddrinfo */

#include "socket.h"

#define MAXBUFLEN 50

/******************************************************************************/

static int GetInternetAddr(struct addrinfo* res, protocol_t prot, host_t host);

/******************************************************************************/

void InitHints(struct addrinfo *hints, int family, int socktype, int flags)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = family;
    hints->ai_socktype = socktype;
    hints->ai_flags = flags;
}

/******************************************************************************/

int GetSocket(char *hostname, const char *port, struct addrinfo *hints, 
protocol_t prot, host_t host)
{
    struct addrinfo *addr_info = NULL;
    int socket = 0;
    int rv = 0;

    if (0 != (rv = getaddrinfo(hostname, port, hints, &addr_info))) 
    {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		return -1;
	}
	
    if (-1 == (socket = GetInternetAddr(addr_info, prot, host)))
    {
        return -1;        
    }

    freeaddrinfo(addr_info);

    return socket;
}

/******************************************************************************/

static int GetInternetAddr(struct addrinfo* res, protocol_t prot, host_t host)
{
    struct addrinfo *runner = NULL;
    int sockfd = 0;
    int yes = 1;
    
    for(runner = res; NULL != runner; runner = runner->ai_next) 
    {
        if (-1 == (sockfd = socket(runner->ai_family, runner->ai_socktype, runner->ai_protocol)))
        {
            perror("listener: socket");
            sockfd = FAIL_SOCKET;
            continue;
        }

        if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) 
        {
            perror("setsockopt");
            return -1;
        }
        
        if ((TCP == prot) && (CLIENT == host) &&
        (-1 == connect(sockfd, runner->ai_addr, runner->ai_addrlen))) 
        {
            close(sockfd);
            perror("client: connect");
            sockfd = FAIL_CONNECT;
            continue;
        }
        
        if ((SERVER == host) && (-1 == bind(sockfd, runner->ai_addr, runner->ai_addrlen)))
        {
            close(sockfd);
            perror("listener: bind");
            sockfd = FAIL_BIND;
            continue;
        }

        break;
    }
    
    if (NULL == runner)
    {
        fprintf(stderr, "talker: failed to create socket\n");
        return -1;
    }
    
    return sockfd;
}

/******************************************************************************/

int UDPDataTransfer(int sockfd)
{
    struct sockaddr_storage their_addr = {0};
    socklen_t addr_len;
    char buffer[MAXBUFLEN] = {0};
    char pong[5] = "pong";
    
    addr_len = sizeof(their_addr);

    if (-1 == (recvfrom(sockfd, buffer, MAXBUFLEN - 1 , 0, 
    (struct sockaddr *)&their_addr, &addr_len))) 
    {
        perror("recvfrom");
        return -1;
    }

    printf("message from client: %s\n", buffer);
    
    if (-1 == (sendto(sockfd, pong, strlen(pong), 0, 
    (struct sockaddr *)&their_addr, addr_len))) 
    {
        perror("sendto");
        return -1;
    }

    return 0;
}

/******************************************************************************/

void CloseConnection(int num_of_bytes, int index, fd_set *master)
{
    if (0 == num_of_bytes) 
    {
        printf("selectserver: socket %d hung up\n", index);
    } 
    else
    {
        perror("recv");
    }

    close(index); 
    FD_CLR(index, master); 
}

/******************************************************************************/

int TCPDataTransfer(int sockfd, fd_set *master)
{
    char msg_to_send[MAXBUFLEN] = {0};
    char buffer[MAXBUFLEN] = {0};   
    int num_of_bytes = 0;
    
    if (STDIN_FILENO == sockfd)
    {
        if (-1 == read(STDIN_FILENO, msg_to_send, sizeof(msg_to_send)))
        {
            perror("read");
            return -1;
        }
        msg_to_send[strlen(msg_to_send) - 1] = '\0';

        if (-1 == write(STDOUT_FILENO, msg_to_send, strlen(msg_to_send)))
        {
            perror("write");
            return -1;
        }

        return 0;
    }
    
    if (0 >= (num_of_bytes = recv(sockfd, buffer, sizeof(buffer), 0))) 
    {
        CloseConnection(num_of_bytes, sockfd, master);
    } 
    
    else  
    {
        printf("message from tcp client: %s\n",buffer);
        if (-1 == send(sockfd, "pong\0", 5, 0))
        {
            perror("send");
            return -1;    
        }
    }

    return 0;   
}
