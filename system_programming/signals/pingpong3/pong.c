#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

void handler(int sig)
{
    write(1, "pong\n", 6);
}

int main(int argc, char *argv[])
{
    pid_t pid = 0;
    size_t j = 0;
    struct sigaction sa;
    
    memset(&sa, 0, sizeof(sa)); 
    sa.sa_handler = handler;
    sigaction(SIGUSR2, &sa, NULL);
    
    while (j < 500)
    {   
        kill(atoi(argv[1]), SIGUSR1);   
        pause();
        ++j;
    }            
    
    return 0;
}
