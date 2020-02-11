#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int sig)
{
    write(1, "pong\n", 6);
}

int main(int argc, char *argv[])
{
    pid_t pid = 0;
    
    struct sigaction sa;
    
    memset(&sa, 0, sizeof(sa)); 
    sa.sa_handler = handler;
    sigaction(SIGUSR2, &sa, NULL);
    
    pid = fork();
    if (0 != pid)
    {  
        while (1)
        {   
            sleep(1); 
            kill(pid, SIGUSR1);   
            pause();
        }            
    }
    
    else 
    {        
        execvp(argv[1], &argv[2]); 
    }    
    
    wait(NULL);
    return 0;
}
