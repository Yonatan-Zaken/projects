#include <unistd.h>     /* fork   */
#include <stdio.h>      /* printf */
#include <sys/types.h>  /* pid_t  */
#include <sys/wait.h>   /* wait   */
#include <stdlib.h>     /* exit   */    
#include <string.h>     /* strlen */
#include <sys/ioctl.h>  /* ioctl  */
#include <signal.h>     /* sigaction */

#define BUFFER_SIZE 10

void pipe_handler(int signum)
{
    printf("pipe signal recieved\n");
    exit(1);
}

int main (int argc, char *argv[])
{
    size_t i = 0;
    int pipe_ping[2], pipe_pong[2];
    int nbytes = 0;
    pid_t cpid;
    char buffer[BUFFER_SIZE] = {0};
    char ping[] = "ping ";
    char pong[] = "pong\n";
    
    struct sigaction sa_pipe;
    memset(&sa_pipe, 0, sizeof(sa_pipe)); 
    sa_pipe.sa_handler = pipe_handler;

    sa_pipe.sa_flags = 0;
    
    sigaction(SIGPIPE, &sa_pipe, NULL);
    
    if (-1 == pipe(pipe_ping))
    {
        perror("pipe");
        exit(EXIT_FAILURE);        
    }
    
    if (-1 == pipe(pipe_pong)) 
    {
       perror("pipe");
       exit(EXIT_FAILURE);
    }
    
    if (-1 == (cpid = fork())) 
    {
       perror("fork");
       exit(EXIT_FAILURE);
    }

    if (0 == cpid) 
    {    
        close(pipe_ping[1]);          
        close(pipe_pong[0]);          

        for (i = 0; i < 100000; ++i)
        {
            read(pipe_ping[0], buffer, BUFFER_SIZE);
            write(STDOUT_FILENO, buffer, strlen(buffer));
            write(pipe_pong[1], pong, strlen(pong)); 
        }
                     
        close(pipe_ping[0]);
        close(pipe_pong[1]);

        exit(EXIT_SUCCESS);
    }

    else      
    {            
        close(pipe_ping[0]);          
        close(pipe_pong[1]);          
    
        for (i = 0; i < 100000; ++i)
        {
            write(pipe_ping[1], ping, strlen(ping));
            read(pipe_pong[0], buffer, BUFFER_SIZE);
            write(STDOUT_FILENO, buffer, strlen(buffer));
        }
        /*
        ioctl(pipe_ping[0], FIONREAD, &nbytes);
        printf("nbytes: %d\n", nbytes);
        */
        close(pipe_ping[1]);          
        close(pipe_pong[0]);
        
        wait(NULL);               
    }

    return 0;
}
