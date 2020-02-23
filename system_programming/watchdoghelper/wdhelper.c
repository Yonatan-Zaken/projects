#include <assert.h> /* assert () */
#include <signal.h> /* kill () */
#include <unistd.h> /* write () */
#include <stdio.h>  /* printf () */

#include "wd.h"
#include "wdhelper.h"

#define ONE_SEC 1

int is_alive = 0;

void HandlerImAlive(int signal)
{
    ++is_alive;
}

int TaskImAlive(void *param)
{
    printf("process id: %d, counter: %d\n", getpid(), is_alive);
    kill(updated_id, SIGUSR1);
}

scheduler_t *WDInit(status_t *status)
{    
    struct sigaction sa1 = {0};
    scheduler_t *s = NULL;
        
    sa1.sa_handler = &HandlerImAlive;
    if (0 != sigaction(SIGUSR1, &sa1, NULL))
    {
        *status = FAIL;
        return NULL;   
    }

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

void *WDSchedulerRun(void *param)
{
    assert(NULL != param);
    sleep(2);
    SchedulerRun((scheduler_t*)param);
}
