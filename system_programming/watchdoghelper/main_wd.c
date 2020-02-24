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
#include <string.h>    /* strcpy () */

#include "scheduler.h"
#include "wdhelper.h"

pid_t updated_id = {0};

static status_t SemaphoreInitIMP(wd_t *wrap, status_t *status)
{
    if (SEM_FAILED == (wrap->sem_p2 = sem_open("/sem_wd_ready", O_CREAT, 0644, 0)))
    {
        *status = FAIL;
        return FAIL;
    }
    
    if (SEM_FAILED == (wrap->sem_p1 = sem_open("/sem_app_ready", O_CREAT, 0644, 0)))
    {
        *status = FAIL;
        return FAIL;
    }
    return SUCCESS;
}

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
    
    wrap->status = WDInit(wrap);
    if (FAIL == wrap->status)
    {
        return 1;
    }
    
    if (FAIL == SemaphoreInitIMP(wrap, status))
    {
        return 1;    
    }
    
    strcpy(wrap->filename, "/home/codesila/git/system_programming/watchdogtimer/outdebug/app");
    
    WDSchedulerRun(wrap);
    
    sem_close(wrap->sem_p1);
    sem_close(wrap->sem_p2);
       
    return 0;
}



