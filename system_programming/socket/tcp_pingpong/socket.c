/*************************
         SOCKET
         C File
    Author : Yonatan Zaken
      Date : 05/04/2020          
*************************/
#include <stdio.h>          /* stderr      */
#include <string.h>         /* memset      */
#include <unistd.h>         /* close       */
#include <errno.h>          /* perror      */
#include <sys/socket.h>     /* socket      */
#include <sys/types.h>      /* struct_addrinfo */
#include <netdb.h>          

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
    struct addrinfo *p = NULL;
    int sockfd = 0;
    
    for(p = res; NULL != p; p = p->ai_next) 
    {
        if (-1 == (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)))
        {
            perror("listener: socket");
            sockfd = FAIL_SOCKET;
            continue;
        }

        if ((SERVER == flag) && (-1 == bind(sockfd, p->ai_addr, p->ai_addrlen)))
        {
            close(sockfd);
            perror("listener: bind");
            sockfd = FAIL_BIND;
            continue;
        }

        break;
    }
    
    if (NULL == p)
    {
        fprintf(stderr, "talker: failed to create socket\n");
        return FAIL_SOCKET;
    }
    
    return sockfd;
}

/******************************************************************************/

