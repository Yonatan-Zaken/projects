/************************************************
*
* File: scheduler_test.c
* Ex: system programing, scheduler
* writer: Israel Drayfus
* Description: run and test functions of scheduler.
*
*************************************************/

#include <stdio.h> /*printf()*/

#include "scheduler.h" /*API header*/

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"

#define TEST(test, errMsg) if (test)\
						   {\
						      printf(GREEN);\
						      printf("%s\n", "SUCCESS");\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf("%s, %s\n", "FAILURE", errMsg);\
						   }\
						   printf(WHITE);

#define UNUSED(param) (void)param

#define DELAY_2 2
#define DELAY_10 10

typedef void (*stop_func)(scheduler_t *s);
typedef void (*remove_func)(scheduler_t *s, ilrd_uid_t uid);

int one = 1, two = 2;

typedef struct StopPack
{
	stop_func func;
	scheduler_t *s;
}stop_pack_t;

typedef struct RemovePack
{
	remove_func func;
	scheduler_t *s;
	ilrd_uid_t uid;
}remove_pack_t;

int PrintTest(void *param)
{
	UNUSED(param);
	
	printf("\033[36m");
	printf("Test\n");
	printf(WHITE);
	
	return 0;
}

int PrintTest2(void *param)
{
	printf("\033[36m");
	printf("Test%d\n", *(int*)param);
	printf(WHITE);
	
	return 0;
}

int Stop(void *param)
{
	((stop_pack_t *)param)->func(((stop_pack_t *)param)->s);
	
	return 0;
}

int Remove(void *param)
{
	printf("\033[36m");
	printf("Remove\n");
	printf(WHITE);
	((remove_pack_t *)param)->func(((remove_pack_t *)param)->s,
	                               ((remove_pack_t *)param)->uid
	                              );
	return 0;
}

void TestTask()
{
	char buff[100];
	ilrd_uid_t uid;
	time_t time = 0;
	
	task_t *task = TaskCreate(PrintTest, (time_t)10, NULL);
	
	uid = TaskGetUid(task);
	strftime (buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&uid.time_stamp));
	printf("Task uid: time: %s, counter: %lu, pid: %d\n", buff, uid.counter, uid.pid);
	
	time = TaskGetTimeToRun(task);
	strftime (buff, 100, "%Y-%m-%d %H:%M:%S",
	          localtime(&time)
	         );
	printf("Task begin_time: %s\n", buff);
	TaskRun(task);
	TaskUpdateTimeToRun(task);
	printf("\n");
	
	TaskDestroy(task);
}

void Test1(scheduler_t *scduler)
{
	stop_pack_t pack = {0};
	ilrd_uid_t uid = {0};
	
	TEST(1 == SchedulerIsEmpty(scduler), "IsEmpty(), True");
	TEST(0 == SchedulerSize(scduler), "Size(), empty list");
	SchedulerAddTask(scduler, PrintTest, DELAY_2, NULL);
	
	pack.func = SchedulerStop;
	pack.s = scduler;
	SchedulerAddTask(scduler, Stop, DELAY_2, &pack);
	TEST(0 == SchedulerIsEmpty(scduler), "IsEmpty(), False");
	TEST(2 == SchedulerSize(scduler), "Size(), two items list");
	printf("run1:");
	SchedulerRun(scduler);
	printf("run2:");
	SchedulerRun(scduler);
	SchedulerClear(scduler);
	TEST(0 == SchedulerSize(scduler), "Size after Clear, empty list");
	
	uid = SchedulerAddTask(scduler, PrintTest2, DELAY_2, &one);
	SchedulerAddTask(scduler, PrintTest2, DELAY_2, &two);
	SchedulerAddTask(scduler, Stop, DELAY_2, &pack);
	printf("\nrun two tasks:\n");
	SchedulerRun(scduler);
	
	SchedulerRemoveTask(scduler, uid);
	printf("\nrun after remove one:\n");
	SchedulerRun(scduler);
}

void Test2(scheduler_t *scduler)
{
	stop_pack_t pack = {0};
	remove_pack_t pack2 = {0};
	
	SchedulerAddTask(scduler, PrintTest, DELAY_2, NULL);
	
	pack2.func = SchedulerRemoveTask;
	pack2.s = scduler;
	pack2.uid = SchedulerAddTask(scduler, Remove, DELAY_2, &pack2);
	
	pack.func = SchedulerStop;
	pack.s = scduler;
	SchedulerAddTask(scduler, Stop, DELAY_10, &pack);
	printf("\nprint delay < stop delay:\n");
	SchedulerRun(scduler);
	printf("\nrun after remove remove itself:\n");
	SchedulerRun(scduler);
	
	printf("\n");
}

int main()
{
	scheduler_t *scduler = {0};
	
	TestTask();
	
	scduler = SchedulerCreate();
	Test1(scduler);
	SchedulerDestroy(scduler);
	
	scduler = SchedulerCreate();
	Test2(scduler);
	SchedulerDestroy(scduler);
	
	return 0;
}
