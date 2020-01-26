/************************************************
*
* File: priorqueue_test.c
* Ex: proiority queue list data structure
* writer: Israel Drayfus
* Description: run and test functions of proiority queue.
*
*************************************************/

#include <stdio.h> /*printf()*/

#include "priorityqueue.h" /*API header*/

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

int one = 1, one2 = 1, two = 2, three = 3, four = 4;
int one_minus = -1;

int Compare(const void *data1, const void *data2, void *param)
{
	UNUSED(param);
	
	return *(int *)data1 - *(int *)data2;
}

int Compare2(const void *data1, const void *data2, void *param)
{
	return *(int *)data1 * *(int *)param - *(int *)data2 * *(int *)param;
}

int IsForErase(void *d1,void *d2)
{
	return d1 == d2;
}

void Test1()
{
	void *n1;
	int one = 1, two = 2, three = 3;
	pq_t *pq = PQCreate(Compare, NULL);
	
	TEST(1 == PQIsEmpty(pq), "IsEmpty, True");
	TEST(0 == PQSize(pq), "Size, empty queue");
	TEST(0 == PQEnqueue(pq, &one), "Enqueue, success return value");
	TEST(1 == PQSize(pq), "Size, size = 1");
	TEST(0 == PQIsEmpty(pq), "IsEmpty, False");
	
	n1 = PQPeek(pq);
	TEST(1 == *(int *)n1, "Peek");
	
	n1 = PQDequeue(pq);
	TEST(1 == *(int *)n1, "Dequeue");
	
	PQEnqueue(pq, &two);
	PQEnqueue(pq, &three);
	n1 = PQPeek(pq);
	TEST(3 == *(int *)n1, "Enqueue, insert highest priority");
	printf("\n");
	
	PQDestroy(pq);
}

void Test2()
{
	void *n1, *n2;
	int one = 1, one2 = 1, two = 2, three = 3;
	pq_t *pq = PQCreate(Compare, NULL);
	
	PQEnqueue(pq, &three);
	PQEnqueue(pq, &two);
	PQEnqueue(pq, &one);
	n1 = PQDequeue(pq);
	n2 = PQDequeue(pq);
	TEST(3 == *(int *)n1, "Enqueue, insert lowest priority (1)");
	TEST(2 == *(int *)n2, "Enqueue, insert lowest priority (2)");
	TEST(1 == *(int *)PQPeek(pq), "Enqueue, insert lowest priority (3)");
	
	PQEnqueue(pq, &two);
	PQEnqueue(pq, &one2);
	n1 = PQDequeue(pq);
	TEST(2 == *(int *)n1, "Enqueue, insert equal priority (1)");
	TEST(1 == *(int *)PQPeek(pq), "Enqueue, insert equal priority (2)");
	PQClear(pq);
	TEST(0 == PQSize(pq), "Size after Clear");
	printf("\n");
	
	PQDestroy(pq);
}

void Test3()
{
	pq_t *pq = PQCreate(Compare, NULL);
	int one = 1, two = 2, three = 3;
	
	PQEnqueue(pq, &one);
	PQEnqueue(pq, &two);
	PQEnqueue(pq, &three);
	TEST(&two == PQErase(pq, IsForErase, &two), "Erase in the meadle, return value");
	TEST(2 == PQSize(pq), "Erase in the meadle, item didn't erased");
	
	TEST(&one == PQErase(pq, IsForErase, &one), "Erase, in the back");
	TEST(1 == PQSize(pq), "Erase in the back, item didn't erased");
	
	PQEnqueue(pq, &two);
	TEST(&three == PQErase(pq, IsForErase, &three), "Erase in the front, return value");
	TEST(&two == PQPeek(pq), "Erase in the front, item didn't erased");
	
	PQDestroy(pq);
}

void Test4()
{
	void *n1, *n2;
	pq_t *pq = PQCreate(Compare2, &one_minus);
	
	PQEnqueue(pq, &one);
	PQEnqueue(pq, &two);
	PQEnqueue(pq, &three);
	n1 = PQDequeue(pq);
	n2 = PQDequeue(pq);
	TEST(1 == *(int *)n1, "Enqueue, insert lowest priority (1)");
	TEST(2 == *(int *)n2, "Enqueue, insert lowest priority (2)");
	TEST(3 == *(int *)PQPeek(pq), "Enqueue, insert lowest priority (3)");
	PQClear(pq);
	
	PQEnqueue(pq, &one);
	PQEnqueue(pq, &two);
	PQEnqueue(pq, &one2);
	n1 = PQDequeue(pq);
	TEST(&one == n1, "Enqueue, insert equal priority (1)");
	TEST(&one2 == PQPeek(pq), "Enqueue, insert equal priority (2)");
	printf("\n");
	
	PQDestroy(pq);
}

int main()
{
	Test1();
	Test2();
	Test3();	
	printf("\npq with parama\n"); 
	Test4();
	
	return 0;
}















