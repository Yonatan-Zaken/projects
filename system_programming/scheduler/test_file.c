/*********************************/
/*   			             	 */
/*   System Programming          */
/*   UID                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/12/19       */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "scheduler.h"

#define UNUSED(x) (void)(x)

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

int PrintTask1(void *param)
{
    printf("Task print: %d\n", *(int*)param);
    
    return 0; 
}

typedef struct Remove
{
    scheduler_t *s;
    ilrd_uid_t uid;
} remove_t;

int RemoveTask(void *param)
{
    SchedulerRemoveTask(((remove_t *)param)->s, ((remove_t *)param)->uid);    
    return 0; 
}

int StopTask(void *param)
{
    SchedulerStop(param);
    
    return 0;
}

static void SchedulerTest1()
{
    int x1 = 1, x2 = 3, x3 = 7;
    ilrd_uid_t uid1;
    ilrd_uid_t uid2;
    scheduler_t *sch1 = NULL;
    remove_t remove;
    
    printf("Scheduler Test1:\n");
    
    sch1 = SchedulerCreate();
    remove.s = sch1;
    
    RUN_TEST(1 == SchedulerIsEmpty(sch1), "sched isempty test1");
    SchedulerAddTask(sch1, &PrintTask1, 10, &x3);
    SchedulerAddTask(sch1, &PrintTask1, 1, &x1);
    uid1 = SchedulerAddTask(sch1, &PrintTask1, 3, &x2);
    uid2 = SchedulerAddTask(sch1, &StopTask, 13, sch1);
    RUN_TEST(4 == SchedulerSize(sch1), "sched size test1");
    SchedulerRun(sch1);
    
    SchedulerAddTask(sch1, &RemoveTask, 4, &remove);
    remove.uid = uid1;
    SchedulerRun(sch1);
    RUN_TEST(4 == SchedulerSize(sch1), "sched size test1");
    
    SchedulerDestroy(sch1);
    
    printf("\n");
}

static void SchedulerTest2()
{
    int x1 = 1, x2 = 2, x3 = 3;
    ilrd_uid_t uid1;
    scheduler_t *sch1 = NULL;
    remove_t remove;
    
    printf("Scheduler Test2:\n");
    
    sch1 = SchedulerCreate();
    remove.s = sch1;
    
    RUN_TEST(1 == SchedulerIsEmpty(sch1), "sched isempty test2");
    
    SchedulerAddTask(sch1, &PrintTask1, 4, &x3);
    while (sleep(2));
    SchedulerAddTask(sch1, &PrintTask1, 4, &x1);
    while (sleep(2));
    SchedulerAddTask(sch1, &PrintTask1, 4, &x2);
    while (sleep(2));
    SchedulerAddTask(sch1, &StopTask, 8, sch1);
    while (sleep(2));
    uid1 = SchedulerAddTask(sch1, &RemoveTask, 2, &remove);
    remove.uid = uid1;
    RUN_TEST(5 == SchedulerSize(sch1), "sched size test2");
    SchedulerRun(sch1);
    SchedulerRun(sch1);
    RUN_TEST(4 == SchedulerSize(sch1), "sched size test2");
    
    SchedulerClear(sch1);
    RUN_TEST(1 == SchedulerIsEmpty(sch1), "sched isempty test2");
    RUN_TEST(0 == SchedulerSize(sch1), "sched size test2");
    
    SchedulerDestroy(sch1);
    
    printf("\n");
}

int main()
{
    SchedulerTest1();
    SchedulerTest2();
    return 0;
}
