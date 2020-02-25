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

#define UNUSED(x) (void)(x)

pid_t updated_id = {0};

static status_t SemaphoreInitIMP(wd_t *wrap, status_t *status)
{
    assert(NULL != wrap);
    assert(NULL != status);
    
    if (SEM_FAILED == (wrap->sem_p2 = sem_open("/sem_wd_ready", O_CREAT, 0644, 0)))
    {
        *status = SYSCALL_FAIL;
        return SYSCALL_FAIL;
    }
    
    if (SEM_FAILED == (wrap->sem_p1 = sem_open("/sem_app_ready", O_CREAT, 0644, 0)))
    {
        *status = SYSCALL_FAIL;
        sem_close(wrap->sem_p2);
        sem_unlink("/sem_wd_ready");
        return SYSCALL_FAIL;
    }
    return SUCCESS;
}

int main(int argc, char *argv[])
{
    status_t stat = SUCCESS;
    status_t *status = &stat;
    wd_t *wrap = NULL; 
    
    UNUSED(argc);

    wrap = malloc(sizeof(*wrap));
    if (NULL == wrap)
    {
        return 1;
    }
        
    updated_id = getppid();
    wrap->status = WDInit(wrap);
    if (SUCCESS != wrap->status)
    {
        free(wrap); wrap = NULL;
        return 1;
    }
    
    if (SUCCESS != SemaphoreInitIMP(wrap, status))
    {
        free(wrap); wrap = NULL;
        return 1;    
    }
    
    strcpy(wrap->exec_filename, argv[0]);
    strcpy(wrap->my_filename, argv[1]);
    
    WDSchedulerRun(wrap);
    
    sem_close(sem_stop_flag);
    printf("FREE WRAP IN MAIN WD\n");
    free(wrap); wrap = NULL;
      
    return 0;
}



