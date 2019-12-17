/*********************************/
/*    System Programming         */
/*    Scheduler                  */       
/*    Author: Guy Cohen Zedek    */
/*    Date: 16/12/2019           */
/*                               */
/*********************************/

#include <stdio.h>
#include <unistd.h> /* sleep */

#include "scheduler.h"

#define MAX_SIZE 20
#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"

#define UNUSED(x) (void)(x)

#define RUN_TEST(test)\
{\
  if(test)\
  {\
    printf(GREEN);\
    printf("SUCCESS\n");\
    printf(RESET);\
  }\
  else\
  {\
    printf(RED);\
    printf("FAIL \n");\
    printf(RESET);\
  }\
}

int g_arr_test[MAX_SIZE];

struct Wrap
{
    scheduler_t *s;
    ilrd_uid_t uid;
};

int Print(void *data)
{
    printf("%d\n", *(int *)data);
    
    return 0;
}

int Stop(void *packet)
{
    SchedulerStop(packet);
    
    return 0;
}

int Remove(void *packet)
{
    struct Wrap *w = (struct Wrap *)packet;
    printf("remove\n");
    SchedulerRemoveTask(w->s, w->uid);
    
    return 0;         
}

static void TestSchedulerCreate()
{
    scheduler_t *s = NULL;

    printf("Scheduler Create:\n");    
    s = SchedulerCreate();

    RUN_TEST(0 == SchedulerSize(s));
    RUN_TEST(1 == SchedulerIsEmpty(s));
    
    SchedulerDestroy(s);    
}

static void TestSchedulerAddTask()
{
    scheduler_t *s = NULL;
    int x = 1;
    
    printf("\nScheduler Add Task:\n");    
    s = SchedulerCreate();

    SchedulerAddTask(s, &Print, 6, &x);
    SchedulerAddTask(s, &Print, 5, &x);
    SchedulerAddTask(s, &Print, 4, &x);
    SchedulerAddTask(s, &Print, 3, &x);
    SchedulerAddTask(s, &Print, 2, &x);
    SchedulerAddTask(s, &Print, 1, &x);
    
    RUN_TEST(6 == SchedulerSize(s));
        
    SchedulerDestroy(s);
}

static void TestSchedulerClear()
{
    scheduler_t *s = NULL;
    int x = 1;
    
    printf("\nScheduler Clear:\n");    
    s = SchedulerCreate();

    SchedulerAddTask(s, &Print, 6, &x);
    SchedulerAddTask(s, &Print, 5, &x);
    SchedulerAddTask(s, &Print, 4, &x);
    SchedulerAddTask(s, &Print, 3, &x);
    SchedulerAddTask(s, &Print, 2, &x);
    SchedulerAddTask(s, &Print, 1, &x);
    
    RUN_TEST(6 == SchedulerSize(s));
    
    SchedulerClear(s);
    RUN_TEST(0 == SchedulerSize(s));
        
    SchedulerDestroy(s);
}

static void TestSchedulerRemove()
{
    scheduler_t *s = NULL;
    int x = 1;
    ilrd_uid_t uid1 = {0};
    ilrd_uid_t uid2 = {0};
    ilrd_uid_t uid3 = {0};
    
    printf("\nScheduler Remove:\n");    
    s = SchedulerCreate();

    SchedulerAddTask(s, &Print, 1, &x);
    SchedulerAddTask(s, &Print, 5, &x);
    SchedulerAddTask(s, &Print, 3, &x);
    uid3 = SchedulerAddTask(s, &Print, 6, &x);
    uid1 = SchedulerAddTask(s, &Print, 4, &x);
    uid2 = SchedulerAddTask(s, &Print, 2, &x);
    
    RUN_TEST(6 == SchedulerSize(s));
    
    SchedulerRemoveTask(s, uid1);
    RUN_TEST(5 == SchedulerSize(s));
    
    SchedulerRemoveTask(s, uid2);
    RUN_TEST(4 == SchedulerSize(s));
    
    SchedulerRemoveTask(s, uid3);
    RUN_TEST(3 == SchedulerSize(s));
        
    SchedulerDestroy(s);
}

static void TestSchedulerRun()
{
    scheduler_t *s = NULL;
    struct Wrap w = {0};
    
    printf("\nScheduler Run:\n"); 
    
    s = SchedulerCreate();
    w.s = s;
    
    SchedulerAddTask(s, &Print, 6, &g_arr_test[6]);
    SchedulerAddTask(s, &Print, 5, &g_arr_test[5]);
    SchedulerAddTask(s, &Print, 4, &g_arr_test[4]);
    SchedulerAddTask(s, &Stop, 10, s);
    SchedulerAddTask(s, &Print, 2, &g_arr_test[2]);
    SchedulerAddTask(s, &Print, 1, &g_arr_test[1]);
    w.uid = SchedulerAddTask(s, &Remove, 7, &w);

    RUN_TEST(7 == SchedulerSize(s));
    
    SchedulerRun(s);
    printf("stop\n");
    SchedulerRun(s);
    RUN_TEST(6 == SchedulerSize(s)); 
    SchedulerDestroy(s);
}

void Initialize()
{
    int i = 0;
    
    for (; i < MAX_SIZE; ++i)
    {
        g_arr_test[i] = i;
    }
}

int main()
{
    Initialize();
    TestSchedulerCreate();
    TestSchedulerAddTask();
    TestSchedulerClear();
    TestSchedulerRemove();
    TestSchedulerRun();
    
    return 0;
}

