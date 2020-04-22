#define _POSIX_C_SOURCE 200112L
#include <stdio.h>        /* printf */
#include <unistd.h>       /* close  */
#include <errno.h>        /* perror */
#include <string.h>       /* strlen */
#include <sys/socket.h>   /* socket */
#include <netdb.h>        /* getaddrinfo */

#include "socket.h"

#define SERVERPORT "4443" 
#define MAXBUFLEN 100

int main(int argc, char *argv[])
{
    int sockfd = 0;
    int rv = 0;
    int broadcast = 1;
    struct addrinfo hints = {0};
    struct addrinfo *res = NULL;
    char buffer[] = "Shomim oti ?";

    if (argc != 2) 
    {
        fprintf(stderr,"usage: broadcaster hostname message\n");
        return 1;
    }

    InitHints(&hints, AF_INET, SOCK_DGRAM, 0);    
    if (0 != (rv = getaddrinfo(argv[1], SERVERPORT, &hints, &res)))
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) 
    {
        perror("socket");
        return 1;
    }

    if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof(broadcast))) 
    {
        perror("setsockopt (SO_BROADCAST)");
        return 1;
    }
    
    if (-1 == (sendto(sockfd, buffer, strlen(buffer), 0, res->ai_addr, 
       res->ai_addrlen))) 
    {
        perror("talker: sendto");
        return 1;
    }

    close(sockfd);

    return 0;
}
