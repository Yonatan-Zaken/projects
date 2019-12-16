#ifndef __TASK_H__
#define __TASK_H__

#include <time.h> /*time_t*/

#include "uid.h" /*UID Functions*/

typedef int (*task_func)(void *param);

typedef struct Task
{
    ilrd_uid_t uid;
    task_func task_func;
    void *param;
    time_t run_time;
    time_t interval;
}task_t;

/*
* TaskCreate() - 
* Returns pointer to the new created Task. 
* complexity of malloc();       
*/
task_t *TaskCreate(task_func to_do, time_t interval, void *param);

/*
* TaskDestroy() - 
* Remove and free Task. 
* complexity of free();       
*/
void TaskDestroy(task_t *t);

/*
* TaskGetUid() - 
* Return Task UID. 
* complexity of O(1);       
*/
ilrd_uid_t TaskGetUid(task_t *t);

/*
* TaskIsMatch() - 
* check if 2 tasks are equal. 
* complexity of O(1);       
*/
int TaskIsMatch(const task_t *t1, const task_t *t2);

/*
* TaskGetTimeToRun() - 
* Return time to start task function. 
* complexity of O(1);       
*/
time_t TaskGetTimeToRun(const task_t *t);

/*
* TaskRun() - 
* Return Value from the called function hold by task. 
* complexity of the called function();       
*/
int TaskRun(const task_t *t);

/*
* TaskUpdateTimeToRun() - 
* Update task next time to run
* complexity of O(1);       
*/
void TaskUpdateTimeToRun(task_t *t);

#endif
