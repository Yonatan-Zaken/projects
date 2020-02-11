#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_handler(int sig)
{
    write(1, "ping\t\n", 7);
    kill(getppid(), SIGUSR2);
}

void parent_handler(int sig)
{
    write(1, "pong\n", 6);
}

int main()
{
    pid_t pid = 0;
    int sig_number = 0;
    sigset_t block;
    
    size_t i = 0, j = 0;
    
    struct sigaction sa_parent;
    struct sigaction sa_child;
    
    memset(&sa_parent, 0, sizeof(sa_parent));
    memset(&sa_child, 0, sizeof(sa_child));
       
    sa_parent.sa_handler = parent_handler;
    sa_child.sa_handler = child_handler;
    
    sigemptyset(&block);
    sigaddset(&block, SIGUSR1);
    sigaddset(&block, SIGUSR2);
    
    sigaction(SIGUSR1, &sa_child, NULL);
    sigaction(SIGUSR2, &sa_parent, NULL);
    
    pid = fork();
    if (0 != pid)
    {  
        while (i < 500)
        {
            kill(pid, SIGUSR1);
            /*sigwait(block, &sig_number);   */
            pause();
            ++i;  
        }
    }
    
    else
    {  
        while (i < 500)
        {    
            /*sigwait(block, &sig_number);   */
            pause();
            ++j;
        }   
    }    
  
    return 0;
}
