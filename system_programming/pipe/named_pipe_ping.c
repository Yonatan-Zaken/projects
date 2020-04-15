#include <stdio.h>      /* printf  */
#include <sys/types.h>  /* mode_t  */
#include <sys/stat.h>   /* mkfifo  */
#include <stdlib.h>     /* exit    */    
#include <string.h>     /* strlen  */
#include <unistd.h>     /* write   */
#include <fcntl.h>      /* O_ flag constants */

int main (int argc, char *argv[])
{
    char buffer[10] = {0};
    char *ping_fifo = "./ping_fifo";
    char *pong_fifo = "./pong_fifo";
    int fd_ping = 0, fd_pong = 0;
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    
    if (-1 == mkfifo(ping_fifo, mode))
    {
        perror("mkfifo");
        return 1;
    }
    
    if (-1 == mkfifo(pong_fifo, mode))
    {
        perror("mkfifo");
        return 1;
    }
    
    printf("ping_fifo waiting for readers...\n");
    if (-1 == (fd_ping = open(ping_fifo, O_WRONLY)))
    {
        perror("open");
        return 1;    
    }
    printf("pong_fifo got readers...\n");
    
    if (-1 == (fd_pong = open(pong_fifo, O_RDONLY)))
    {
        perror("open");
        return 1;
    }
    
    while (1)
    {
        if (-1 == write(fd_ping, "ping\n", 5))
        {
            perror("write");
            return 1;
        }
        
        if (-1 == read(fd_pong, buffer, 10))
        {
            perror("read");
            return 1;
        }        

        write(STDOUT_FILENO, buffer, strlen(buffer));
    }
       
    return 0;
}
