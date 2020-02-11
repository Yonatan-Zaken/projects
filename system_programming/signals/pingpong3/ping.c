#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int sig, siginfo_t *info, void *ucontext)
{
    write(1, "ping\n", 6);
    kill(info->si_pid, SIGUSR2);
}

int main(int argc, char *argv[])
{
    pid_t pid = 0;
    size_t i = 0;
    struct sigaction sa;
    
    memset(&sa, 0, sizeof(sa)); 
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    
    while (i < 500)
    {   
        pause();
        ++i; 
    }            
    
    return 0;
}
