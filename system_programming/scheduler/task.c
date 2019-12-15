/*********************************/
/*   			             	 */
/*   System Programming          */
/*   Task                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/12/19       */
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/
#include <time.h> /*time_t*/

#include "task.h" /* Task Functions */
#include "uid.h" /*UID Functions*/

struct Task
{
    ilrd_uid_t uid;
    task_func *taskfunc;
    void *param;
    time_t begin_time;
    time_t interval;
};

task_t *TaskCreate(task_func to_do, time_t interval, void *param)
{

}

void TaskDestroy(task_t *t)
{

}

ilrd_uid_t TaskGetUid(task_t *t)
{

}

int TaskIsMatch(const task_t *t1, const task_t *t2)
{

}

time_t TaskGetTimeToRun(const task_t *t)
{

}

int TaskRun(const task_t *t)
{

}

void TaskUpdateTimeToRun(task_t *t)
{

}
