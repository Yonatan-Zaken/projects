#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ARGUMENTS 3

void WatchDogFork(char *argv[])
{
    pid_t pid;
    
    assert(NULL != argv);
    
    while (1)
    {
        pid = fork();
        if (0 != pid)
        {
            wait(NULL);
        }
        
        else
        {
            execvp(argv[2], &argv[3]);
        }
    } 
}

void WatchDogSystem(char *argv[])
{
    assert(NULL != argv);
    while (1)
    {
        system(argv[2]);
    }           
}

int main(int argc, char *argv[])
{
    assert(ARGUMENTS <= argc);
    
    printf("%d\n", argc);
    if (0 == strcmp(argv[1], "fork"))
    {
        WatchDogFork(argv);
    }
    
    else
    {
        WatchDogSystem(argv);
    }
 
    return 0;
}
