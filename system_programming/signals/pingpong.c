#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

static volatile int flag = 0;

void handler(int sig)
{
    if (SIGUSR1 == sig)
    {
        flag = 1;     
    }
    else
    {
        flag = 0;  
    }
}

int main()
{
    pid_t pid = 0;
    pid_t ppid = 0;
    
    struct sigaction sa;
    sigset_t block;
    
    sigemptyset(&block);
    sigaddset(&block, SIGUSR1);
    sigaddset(&block, SIGUSR2);
    
    sa.sa_handler = handler;
    sa.sa_mask = block;
    sa.sa_flags = 0;
    
    sigaction(SIGUSR2, &sa, NULL);
    pid = fork();
    if (0 != pid)
    {  
        while (1)
        {
            if (0 == flag)
            {
                printf("ping\n");
                kill(pid, SIGUSR1);   
                sigaction(SIGUSR2, &sa, NULL);
            }
        }
    }
    
    else if (0 == pid)
    {
        ppid = getppid();
        sigaction(SIGUSR1, &sa, NULL);    
        while (1)
        {
            if (1 == flag)
            {
                printf("pong\n");
                kill(ppid, SIGUSR2);    
                sigaction(SIGUSR1, &sa, NULL);
            }
        }   
    }    
    
    return 0;
}
