/*********************************/
/*   			             	 */
/*   System Programming          */
/*   Scheduler                   */
/*   Author: Yonatan Zaken       */
/*   Last Updated 17/12/19       */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stddef.h>	/*size_t*/
#include <time.h>	/*time_t*/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep */

#include "priorityqueue.h" /*priority functions*/
#include "task.h" /*task functions*/

#define FREE(ptr) {free(ptr); ptr = NULL;}

struct Scheduler
{
    pq_t *q;
    int remove_current;
    int stop_flag;
    task_t *current_task;
};

int PriorityFunc(const void *node_data, const void *user_data, void *param)
{
    task_t *t1 = (task_t *)node_data;
    task_t *t2 = (task_t *)user_data;
    return (TaskGetTimeToRun(t1) - TaskGetTimeToRun(t2));
}

scheduler_t *SchedulerCreate()
{
    scheduler_t *new_sch = (scheduler_t *)malloc(sizeof(scheduler_t));
    if (NULL != new_sch)
    {
        new_sch->q = PQCreate(&PriorityFunc, NULL);
        if (NULL != new_sch->q)
        {
            new_sch->remove_current = 0;
            new_sch->stop_flag = 1;
            new_sch->current_task = NULL; 
            return new_sch;
        }
        
        FREE(new_sch->q);
        return NULL;
    }
    
    return NULL;  
}

void SchedulerDestroy(scheduler_t *s)
{
    size_t size = SchedulerSize(s);
    
    while (0 < size)
    {
        TaskDestroy(PQDequeue(s->q));
        --size;
    }
    
    PQDestroy(s->q);
    FREE(s);
}

ilrd_uid_t SchedulerAddTask(scheduler_t *s, task_func to_do, time_t interval, void *param)
{
    task_t *new_task = NULL;    
    ilrd_uid_t bad_uid = {0};
    
    assert(NULL != s);
    
    new_task = TaskCreate(to_do, interval, param);
    
    if (NULL == new_task)
    {
        return bad_uid;
    }
    
    PQEnqueue(s->q, new_task);    
    
    return new_task->uid;
}

int CompareUid(void *task1, void *task2)
{
    return (UIDIsSame(((task_t*)task1)->uid,((task_t*)task2)->uid));
}

void SchedulerRemoveTask(scheduler_t *s, ilrd_uid_t uid)
{
    void *temp = NULL;
    
    assert(NULL != s);    
    
    if (NULL != s->current_task && 1 == UIDIsSame(s->current_task->uid, uid))
    {
        s->remove_current = 1;
        return;
    }
    
    temp = PQErase(s->q, &CompareUid, &uid);
    if (NULL != temp)
    {
        TaskDestroy(temp);
    }
          
}

void SchedulerRun(scheduler_t *s)
{
    task_t *new_task = NULL;    
    
    assert(NULL != s);
    
    s->stop_flag = 1;
    
    while (1 == s->stop_flag)
    {
        new_task = PQDequeue(s->q);
        s->current_task = new_task;
        
        if (time(NULL) < TaskGetTimeToRun(s->current_task))
        {
            while (sleep(TaskGetTimeToRun(new_task) - time(NULL)));
        }
        
        if ((0 == TaskRun(new_task)) && (0 == s->remove_current))
        {
            TaskUpdateTimeToRun(new_task);
            PQEnqueue(s->q, new_task);
        }   

        else
        {
            TaskDestroy(new_task);
            s->remove_current = 0;
        }
    }
}

void SchedulerStop(scheduler_t *s)
{
    assert(NULL != s);
    
    s->stop_flag = 0;
}

size_t SchedulerSize(const scheduler_t *s)
{
    assert(NULL != s);
    
    return PQSize(s->q);
}

int SchedulerIsEmpty(const scheduler_t *s)
{
    assert(NULL != s);
    
    return PQIsEmpty(s->q);
}

void SchedulerClear(scheduler_t *s)
{
    size_t size = 0;
    void *temp = NULL;
    
    assert(NULL != s);
    
    size = SchedulerSize(s);
    
    while (0 < size)
    {
        temp = PQDequeue(s->q);
        TaskDestroy(temp);
        --size;
    }
}
