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
};

pid_t updated_id;

scheduler_t *WDInit(status_t *status);

void *WDSchedulerRun(void *param);

int TaskImAlive(void *param);

#endif
