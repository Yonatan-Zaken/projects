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

/******************************************************************************/

void InitHints(struct addrinfo *hints, int family, int socktype, int flags)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = family;
    hints->ai_socktype = socktype;
    hints->ai_flags = flags;
}

/******************************************************************************/

int GetInternetAddr(struct addrinfo* res, flag_t flag)
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

        if ((SERVER == flag) && (-1 == bind(sockfd, runner->ai_addr, runner->ai_addrlen)))
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
