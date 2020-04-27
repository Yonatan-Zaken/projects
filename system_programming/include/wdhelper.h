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
    char my_filename[100];
    char exec_filename[100];
    status_t status;
};

pid_t updated_id;

sem_t *sem_stop_flag;

/* Gets a struct of type WatchDog and initializes its members.
*  Initializes the sigaction for both signal handlers,
*  Semaphores of the sem_stop_flag 
*  Returns SUCCESS if no error occured, otherwise FAIL
*/
status_t WDInit(wd_t *wrap);

/* Runs the scheduler of both proccesses*/
void *WDSchedulerRun(void *param);

/* Destroys the scheduler of both proccesses */
void WDCleanUp(void *param);

#endif /* WD_HELPER */
