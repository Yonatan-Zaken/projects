#ifndef __WDHELPER_H__
#define __WDHELPER_H__

#include <sys/types.h> /* pid_t */
#include <pthread.h>   /* pthread_t */
#include <semaphore.h> /* sem_t */

#include "wd.h"
#include "scheduler.h"

struct WatchDog
{
    pthread_t thread;
    scheduler_t *s;
    sem_t *sem_p1;
    sem_t *sem_p2;
    char filename[100];
    status_t status;
};

pid_t updated_id;

sem_t *sem_stop_flag = NULL;

status_t WDInit(wd_t *wrap);

void *WDSchedulerRun(void *param);

void WDCleanUp(void *param);

#endif
