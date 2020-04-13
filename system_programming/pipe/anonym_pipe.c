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
    int pipefd_1[2], pipefd_2[2];
    pid_t cpid;
    char buffer[BUFFER_SIZE] = {0};
    char ping[] = "ping ";
    char pong[] = "pong\n";
    
    if (-1 == pipe(pipefd_1))
    {
        perror("pipe");
        exit(EXIT_FAILURE);        
    }
    
    if (-1 == pipe(pipefd_2)) 
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
        close(pipefd_1[1]);          
        close(pipefd_2[0]);          

        for (i = 0; i < 50; ++i)
        {
            read(pipefd_1[0], buffer, BUFFER_SIZE);
            write(pipefd_2[1], pong, strlen(pong)); 
            write(STDOUT_FILENO, buffer, strlen(buffer));
        }
                               
        

        close(pipefd_1[0]);
        close(pipefd_2[1]);

        _exit(EXIT_SUCCESS);
    }

    else       /* Parent writes argv[1] to pipe */
    {            
        close(pipefd_1[0]);          /* Close unused read end */
        close(pipefd_2[1]);          /* Close unused write end */
    
        for (i = 0; i < 50; ++i)
        {
            write(pipefd_1[1], ping, strlen(ping));
            read(pipefd_2[0], buffer, BUFFER_SIZE);
            write(STDOUT_FILENO, buffer, strlen(buffer));
        }
        
        close(pipefd_1[1]);          
        close(pipefd_2[0]);

        wait(NULL);               
    }

    return 0;
}
