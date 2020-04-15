#include <unistd.h>     /* fork   */
#include <stdio.h>      /* printf */
#include <sys/types.h>  /* pid_t  */
#include <sys/wait.h>   /* wait   */
#include <stdlib.h>     /* exit   */    
#include <string.h>     /* strlen */

#define BUFFER_SIZE 10

int main (int argc, char *argv[])
{
    size_t i = 0;
    int pipe_ping[2], pipe_pong[2];
    pid_t cpid;
    char buffer[BUFFER_SIZE] = {0};
    char ping[] = "ping ";
    char pong[] = "pong\n";
    
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

        for (i = 0; ; ++i)
        {
            read(pipe_ping[0], buffer, BUFFER_SIZE);
            write(STDOUT_FILENO, buffer, strlen(buffer));
            write(pipe_pong[1], pong, strlen(pong)); 
        }
                               
        close(pipe_ping[0]);
        close(pipe_pong[1]);

        exit(EXIT_SUCCESS);
    }

    else       /* Parent writes argv[1] to pipe */
    {            
        close(pipe_ping[0]);          /* Close unused read end */
        close(pipe_pong[1]);          /* Close unused write end */
    
        for (i = 0; ; ++i)
        {
            write(pipe_ping[1], ping, strlen(ping));
            read(pipe_pong[0], buffer, BUFFER_SIZE);
            write(STDOUT_FILENO, buffer, strlen(buffer));
        }
        
        close(pipe_ping[1]);          
        close(pipe_pong[0]);

        wait(NULL);               
    }

    return 0;
}
