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
#include <unistd.h>    /* getpid() */
#include <pthread.h>   /* pthread_create () */
#include <fcntl.h>     /* For O_* constants */
#include <sys/stat.h>  /* For mode constants */
#include <semaphore.h> /* sem_open () */
#include <signal.h>    /* sigaction () */
#include <assert.h>    /* assert() */

#include "scheduler.h"
#include "wd.h"

#define ONE_SEC 1
#define THREE_SEC 3

struct WatchDog
{
    pthread_t thread;
    scheduler_t *s;
    sem_t *sem_p1;
    sem_t *sem_p2;
};

enum
{
    SUCCESS,
    FAIL
};

size_t is_wd_alive = 0;
pid_t updated_id = {0};

sem_t sem_is_wd_up = {0};
sem_t sem_top_flag = {0};
sem_t sem_wd_ready = {0};
sem_t sem_app_ready = {0};


void HandlerStopSignIMP(int signal)
{

}

void HandlerImAliveIMP(int signal)
{
    ++is_wd_alive;
}

int TaskImAlive(void *param)
{
    write(1, "ping\n", 5);
    kill(updated_id, SIGUSR1);
}

scheduler_t *WDInitIMP(enum *status)
{    
    struct sigaction sa1 = {0};
    scheduler_t *s = NULL;
        
    sa1.sa_handler = &HandlerImAliveIMP;
    
    if (NULL != (s = SchedulerCreate()))
    {
        if (!UIDIsBad(SchedulerAddTask(s, &TaskImAlive, ONE_SEC, NULL))) 
        {
            *status = SUCCESS;
            return s;
        }
        SchedulerDestroy(s);
    }
    *status = FAIL;
    return NULL;
}

void *SchedulerRunIMP(void *param)
{
    assert(NULL != pack);
    sleep(5);
    SchedulerRun(((wd_t*)param)->s);
    
}

wd_t *WDStart(const char *filename, enum *status)
{
    wd_t *wrap = NULL;
    pit_t pid = {0};
    
    assert(NULL != filename);
    
    wrap = malloc(*wrap)
    if (NULL != wrap)
    {
        wrap->s = WDInitIMP(status);
        if (NULL != wrap->s)
        {
            wrap->thread = {0};
        }
        free(wrap); wrap = NULL;
        return wrap;
    }
    
    if (0 != pthread_create(wrap->thread, NULL, SchedulerRunIMP, wrap))
    {
        *status = FAIL;
        return NULL;
    }
    
    if (0 == (pid = fork()))
    {
        exec()    
    }    
    else
    {
        updated_id = pid;
    }
      
}

void WDStop(wd_t *wd)
{

}
