#ifndef __SHCEDULER_H__
#define __SHCEDULER_H__

#include <stddef.h>	/*size_t*/
#include <time.h>	/*time_t*/

#include "task.h"	/*Task Functions*/

typedef struct Scheduler scheduler_t;

/*
* SchedulerCreate() - 
* Returns pointer to the Scheduler. 
* complexity of malloc();       
*/
scheduler_t *SchedulerCreate();

/*
* SchedulerDestroy() -
* Destroys and frees Scheduler from memory.
* complexity of free();                  
*/
void SchedulerDestroy(scheduler_t *s);

/*
* SchedulerAddTask()-
* Gets pointer to Scheduler, interval between each occurrence 
* + function to operate this task and additional paramter
* Returns: 0 - Success | ~0 - Failure
* complexity of malloc();               
*/
ilrd_uid_t SchedulerAddTask(scheduler_t *s, task_func to_do, time_t interval, void *param);

/*
* SchedulerRemoveTask()-
* Gets pointer to Scheduler and spesific UID for remove.
* if there is an active task need to be removed 
* + Scheduler will wait for it to finish 
* complexity of O(n)               
*/
void SchedulerRemoveTask(scheduler_t *s, ilrd_uid_t uid);

/*
* SchedulerRun() - 
* Active the Scheduler and start the tasks functions Scheduling
* complexity of O(infinite);              
*/
void SchedulerRun(scheduler_t *s);

/*
* SchedulerStop() - 
* Stop the Scheduler and stop all tasks functions Scheduling
* complexity of O(1);              
*/
void SchedulerStop(scheduler_t *s);

/*
* SchedulerSize() - 
* Return number of tasks in the Scheduler
* complexity of O(n);              
*/
size_t SchedulerSize(const scheduler_t *s);

/*
* SchedulerIsEmpty() - 
* Return 1 - Scheduler is empty | 0 - Scheduler not empty.
* complexity of O(1);              
*/
int SchedulerIsEmpty(const scheduler_t *s);

/*
* SchedulerClear() - 
* Clear/Empty the Scheduler from tasks
* if there is active task it will wait for it finish and then clear the Scheduler
* complexity of O(n);              
*/
void SchedulerClear(scheduler_t *s);

#endif
