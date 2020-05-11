/*************************
         SELECT
         C File
    Author : Yonatan Zaken
      Date : 05/04/2020          
*************************/
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>       /* stderr      */
#include <stdlib.h>
#include <string.h>      /* memset      */
#include <unistd.h>      /* close       */
#include <sys/types.h>   
#include <sys/socket.h>  /* socket      */
#include <netinet/in.h>
#include <arpa/inet.h>   /* inet_ntop   */
#include <netdb.h>       /* getaddrinfo */
#include <sys/select.h>  /* select      */

#include "socket.h"

#define PORT "4443"   /* port we're listening on*/
#define BACKLOG 10
#define MAXBUFLEN 50

/******************************* declarations ********************************/
/*int GetSocket(int family, int socktype, int flags);*/
/*int SearchInternetAddr(struct addrinfo* node);*/
void InitTimeVal(struct timeval *tv);
void HandleConnections(fd_set *master, int *fdmax, int listener);
void CloseConnection(int nbytes, int index, fd_set *master);
int TCPDataTransfer(int sockfd, fd_set *master);
int UDPDataTransfer(int sockfd);
int MonitorSockets(int listener, int udp_fd);

/*****************************************************************************/

int main(int argc, char *argv[])
{
    int listener = 0;
    int udp_fd = 0;     
    struct addrinfo hints = {0};
    
    InitHints(&hints, AF_INET, SOCK_STREAM, AI_PASSIVE);
    
    if (-1 == (listener = GetSocket("y10", PORT, &hints, TCP, SERVER)))
    {
        return 1;
    }

    if (-1 == listen(listener, BACKLOG)) 
    {
        perror("listen");
        close(listener);
        return 1;
    }

    InitHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);

    if (-1 == (udp_fd = GetSocket("y10", PORT, &hints, UDP, SERVER)))
    {
        return 1;
    }
    
    if (-1 == MonitorSockets(listener, udp_fd))
    {
        return 1;
    }

    return 0;
}

/******************************************************************************/
/*
int GetSocket(int family, int socktype, int flags)
{
    struct addrinfo hints = {0};
    struct addrinfo *addr_info = NULL;
    int socket = 0;
    int rv = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = socktype;
    hints.ai_flags = flags;

    if (0 != (rv = getaddrinfo(NULL, PORT, &hints, &addr_info))) 
    {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		return -1;
	}
	
    if (-1 == (socket = SearchInternetAddr(addr_info)))
    {
        return -1;        
    }

    freeaddrinfo(addr_info);

    return socket;
}
*/

void InitTimeVal(struct timeval *tv)
{
    tv->tv_sec = 5;
    tv->tv_usec = 0;
}

/*
int SearchInternetAddr(struct addrinfo* node)
{
    struct addrinfo *runner = NULL;
    int sockfd = 0;
    int yes = 1;
    
    for(runner = node; runner != NULL; runner = runner->ai_next) 
    {
        if (-1 == (sockfd = socket(runner->ai_family, runner->ai_socktype, 
        runner->ai_protocol))) 
        {
            perror("server: socket");
            continue;
        }
        
        if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) 
        {
            perror("setsockopt");
            return -1;
        }
        
        if (-1 == bind(sockfd, runner->ai_addr, runner->ai_addrlen)) 
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        
        break;
    }
    
    if (NULL == runner) 
    {
        fprintf(stderr, "server: failed to bind\n");
        sockfd = -1;
    }
    
    return sockfd;
}
*/
/******************************************************************************/

void HandleConnections(fd_set *master, int *fdmax, int listener)
{
    struct sockaddr_storage remoteaddr = {0}; 
    socklen_t addrlen = {0};
    int newfd = 0;        
    char remoteIP[INET_ADDRSTRLEN] = {0};

    addrlen = sizeof(remoteaddr);

    newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
    if (-1 == newfd) 
    {
        perror("accept");
    } 

    else 
    {
        FD_SET(newfd, master); 
        if (newfd > *fdmax) 
        {   
            *fdmax = newfd;
        }
        printf("selectserver: new connection from %s on socket %d\n",
            inet_ntop(remoteaddr.ss_family, 
            &(((struct sockaddr_in *)&remoteaddr)->sin_addr), remoteIP, INET_ADDRSTRLEN), newfd);
    }
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

int MonitorSockets(int listener, int udp_fd)
{
    fd_set master = {0};
    fd_set read_fds = {0};
    struct timeval tv = {0};
    int fdmax = 0;
    int i = 0;

    InitTimeVal(&tv);

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    FD_SET(listener, &master);
    FD_SET(udp_fd, &master);
    FD_SET(STDIN_FILENO, &master);

    fdmax = listener > udp_fd ? listener : udp_fd;
    
    while(1) 
    {
        read_fds = master; 
        if (-1 == select(fdmax+1, &read_fds, NULL, NULL, &tv)) 
        {
            perror("select");
            return 1;
        }

        for(i = 0; i <= fdmax; ++i) 
        {
            if (FD_ISSET(i, &read_fds)) 
            { 
                if (i == listener) 
                {
                    HandleConnections(&master, &fdmax, listener);
                }
                
                else if (i == udp_fd)
                {
                    if (-1 == UDPDataTransfer(i))
                    {
                        close(i); 
                        FD_CLR(i, &master);
                    }      
                }

                else if (-1 == TCPDataTransfer(i, &master))
                {
                    close(i); 
                    FD_CLR(i, &master);  
                }
            } 
        } 
    }

    return 0; 
}
