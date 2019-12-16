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
}remove_t;

int RemoveTask(void *param)
{
    return SchedulerRemoveTask(((remove_t *)param)->s, ((remove_t *)param)->uid);
}

static void SchedulerTest1()
{
    int x1 = 1, x2 = 3, x3 = 7;
    
    scheduler_t *sch1 = NULL;
    
    printf("Scheduler Test1:\n");
    
    sch1 = SchedulerCreate();
    RUN_TEST(1 == SchedulerIsEmpty(sch1), "sched isempty test1");
    SchedulerAddTask(sch1, &PrintTask1, 10, &x3);
    SchedulerAddTask(sch1, &PrintTask1, 1, &x1);
    SchedulerAddTask(sch1, &PrintTask1, 3, &x2);
    RUN_TEST(3 == SchedulerSize(sch1), "sched size test1");
    SchedulerRun(sch1);
    
    SchedulerDestroy(sch1);
    
    printf("\n");
}

int main()
{

    SchedulerTest1();
    return 0;
}
