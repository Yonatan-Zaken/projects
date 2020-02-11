#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void handler(int sig)
{
    write(1, "ping\t\n", 7);
    kill(getppid(), SIGUSR2);    
}

int main ()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);
    
    while (1)
    {
        pause();
    }
               
    return 0;
}
