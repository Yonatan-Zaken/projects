#include <assert.h>    /* assert () */
#include <signal.h>    /* kill () */
#include <unistd.h>    /* write () */
#include <stdio.h>     /* printf () */
#include <fcntl.h>     /* For O_* constants */
#include <sys/stat.h>  /* For mode constants */
#include <sys/types.h> /* pid_t */
#include <semaphore.h> /* sem_open () */

#include "wdhelper.h"

#define UNUSED(x) (void)(x)
#define ONE_SEC 1
#define THREE_SEC 3

int is_alive = 0;

/******************************* Handler Functions **************************/
void HandlerImAlive(int signal)
{
    UNUSED(signal);
    printf("current process :%d, counter: %d\n", getpid(), is_alive);
    ++is_alive;
}

void HandlerStopSign(int signal)
{
    UNUSED(signal);
    printf("current process :%d\n", getpid());
    sem_post(sem_stop_flag);
}

/******************************* Task Functions *****************************/
int TaskImAlive(void *param)
{
    int sval = 0;
    UNUSED(param);
    
    sem_getvalue(sem_stop_flag, &sval);
    printf("before if - sval = %d\n", sval);
    if (0 != sval)
    {
        printf("inside if - sval = %d\n", sval);
        SchedulerStop(((scheduler_t*)param));
    }
    else
    {
        kill(updated_id, SIGUSR1);    
    }
    
    return 0;
}

int TaskIsAlive(void *param)
{
    pid_t pid = {0};
    
    assert(NULL != param);
    printf("Welcome to the second task\n");
    if (0 == is_alive)
    {
        kill(updated_id, SIGKILL);
        if (0 == (pid = fork()))
        {
            printf("you are in the exec of the second task\n");
            execl(((wd_t *)param)->filename , ((wd_t *)param)->filename, NULL);        
        }
        else
        {
            updated_id = pid;
        }
        SchedulerStop(((wd_t *)param)->s);
    }   
    
    is_alive = 0;
    return 0;        
}

/******************************** Additional Functions ***************************/

status_t WDInit(wd_t *wrap)
{ 
    struct sigaction sa1 = {0};
    struct sigaction sa2 = {0};   
    
    if (SEM_FAILED == (sem_stop_flag = sem_open("/sem_stop_flag", O_CREAT, 0644, 0)))
    {
        wrap->status = FAIL;
        return FAIL;    
    }
          
    sa1.sa_handler = &HandlerImAlive;
    if (0 != sigaction(SIGUSR1, &sa1, NULL))
    {
        wrap->status = FAIL;
        return FAIL;   
    }

    sa2.sa_handler = &HandlerStopSign;
    if (0 != sigaction(SIGUSR2, &sa2, NULL))
    {
        wrap->status = FAIL;
        return FAIL;   
    }    
    
    if (NULL != (wrap->s = SchedulerCreate()))
    {
        if (!UIDIsBad(SchedulerAddTask(wrap->s, &TaskImAlive, ONE_SEC, wrap->s))) 
        {
            if (!UIDIsBad(SchedulerAddTask(wrap->s, &TaskIsAlive, THREE_SEC, wrap)))
            {
                wrap->status = SUCCESS;
                return SUCCESS;
            } 
        }    
    }
    wrap->status = FAIL;
    SchedulerDestroy(wrap->s);        
    return FAIL;
}

void *WDSchedulerRun(void *param)
{
    int sem_value = 0;
    
    assert(NULL != param);
    while (0 == sem_value)
    {
        sem_getvalue(sem_stop_flag, &sem_value);
        sem_post(((wd_t *)param)->sem_p1);
        sem_wait(((wd_t *)param)->sem_p2);
        SchedulerRun(((wd_t*)param)->s);
    }
    
    WDCleanUp((wd_t*)param);
    return NULL;
}

void WDCleanUp(void *param)
{
    printf("scheduler cleanup\n");
    SchedulerDestroy(((wd_t*)param)->s);
    sem_close(sem_stop_flag);
}
