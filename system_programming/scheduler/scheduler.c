/*********************************/
/*   			             	 */
/*   System Programming          */
/*   Scheduler                   */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/12/19       */
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/

#include <stddef.h>	/*size_t*/
#include <time.h>	/*time_t*/

#include "priorityqueue.h" /* Priority Queue functions */
#include "scheduler.h"	/*Task Functions*/

struct Scheduler
{
    pq_t *q;
    int remove_current_flag;
    int stop_flag;
    task_t *current_task;
};

scheduler_t *SchedulerCreate()
{
    
}

void SchedulerDestroy(scheduler_t *s)
{

}

int SchedulerAddTask(scheduler_t *s, task_func to_do, time_t interval, void *param)
{
}

void SchedulerRemoveTask(scheduler_t *s, ilrd_uid_t uid)
{


}

void SchedulerRun(const scheduler_t *s)
{

}

void SchedulerStop(const scheduler_t *s)
{

}

size_t SchedulerSize(const scheduler_t *s)
{

}

int SchedulerIsEmpty(const scheduler_t *s)
{

}

void SchedulerClear(scheduler_t *s)
{

}
