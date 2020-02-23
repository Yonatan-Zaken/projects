/*********************************/
/*   			             	 */
/*   System Programming          */
/*   Watch Dog Timer             */
/*   Author: Yonatan Zaken       */
/*   Last Updated 20/2/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/
#include <sys/types.h> /* pid_t */
#include <stdlib.h>    /* malloc () */
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

#define ONE_SEC 1
#define THREE_SEC 3

pid_t updated_id = {0};

sem_t sem_is_wd_up = {0};
sem_t sem_top_flag = {0};
sem_t sem_wd_ready = {0};
sem_t sem_app_ready = {0};

wd_t *WDStart(const char *filename, status_t *status)
{
    wd_t *wrap = NULL;
    pid_t pid = {0};
    
    assert(NULL != filename);
    
    wrap = malloc(sizeof(*wrap));
    if (NULL != wrap)
    {
        wrap->s = WDInit(status);
        if (NULL == wrap->s)
        {
            free(wrap); wrap = NULL;
            return wrap;
        }
        
    }
    
    else
    {
        return NULL;
    }
    
    if (0 == (pid = fork()))
    {
        execl("/home/codesila/git/system_programming/watchdoghelper/outdebug/main_wd_out", "/home/codesila/git/system_programming/watchdoghelper/outdebug/main_wd_out", NULL);                                                   
    }    
    else
    {
        updated_id = pid;
    }
    
    if (0 != pthread_create(&(wrap->thread), NULL, &WDSchedulerRun, wrap->s))
    {
        *status = FAIL;
        return NULL;
    }
    
    return wrap;
}

void WDStop(wd_t *wd)
{
    assert(NULL != wd);
    pthread_join(wd->thread, NULL);
}
