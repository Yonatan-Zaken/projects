#include <stdlib.h>    /* malloc */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* getpid() */
#include <pthread.h>   /* pthread_create () */
#include <fcntl.h>     /* For O_* constants */
#include <sys/stat.h>  /* For mode constants */
#include <semaphore.h> /* sem_open () */
#include <signal.h>    /* sigaction () */
#include <assert.h>    /* assert() */
#include <stdio.h>     /* printf () */

#include "scheduler.h"
#include "wdhelper.h"
#include "wd.h"

pid_t updated_id = {0};

int main(int argc, char *argv[])
{
    status_t stat = SUCCESS;
    status_t *status = &stat;
    wd_t *wrap = NULL; 
    
    wrap = malloc(sizeof(*wrap));
    if (NULL == wrap)
    {
        return 1;
    }
        
    updated_id = getppid();
    
    wrap->s = WDInit(status);
    if (NULL == wrap->s)
    {
        return 1;
    }

    WDSchedulerRun(wrap->s);
       
    return 0;
}



