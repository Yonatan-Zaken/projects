
/*******************************************************************************
-Ws Sorted linked list
-Itai Marienberg
-Dec 10 2019    
*******************************************************************************/

#include <stdio.h>  /*printf */

#include "priorityqueue.h" /* sorted linked list functions */

#define UNUSED(x) (void)(x)
#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"

#define RUN_TEST(test,mssg)\
            if (test)\
            {\
                printf(GREEN "SUCCESS: %s\n",mssg);\
                printf(RESET);\
            }\
            else\
            {\
                printf(RED "FAIL: %s\n",mssg);\
                printf(RESET);\
            }\

int MatchFunc(void *data, void *additional)
{   
    return (*(int*)data == *(int*)additional);
}

int CmpFunc(const void *node_data, const void *user_data, void *param)
{
    UNUSED(param);
    return (*(int *)node_data - *(int *)user_data);
}

static void Test()
{
    pq_t *pq = NULL;

    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 4;

    printf("PQ Test 1:\n");  
    pq = PQCreate(&CmpFunc, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(1 == *(int *)PQPeek(pq), "peek");
    RUN_TEST(1 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(2 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(2 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(3 == *(int *)PQDequeue(pq), "Dequeue");
    PQDestroy(pq);
    
    printf("PQ Test 2:\n");  
    pq = PQCreate(&CmpFunc, NULL);
    RUN_TEST(0 == PQSize(pq), "size");
    RUN_TEST(1 == PQIsEmpty(pq), "size");
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(1 == PQSize(pq), "size");

    PQDestroy(pq); 
    
    printf("PQ Test 3:\n");  
    pq = PQCreate(&CmpFunc, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(2 == *(int*)PQErase(pq, &MatchFunc, &x2), "erase");
    RUN_TEST(3 == PQSize(pq), "size");
    RUN_TEST(NULL == PQErase(pq, &MatchFunc, &x4), "erase");
 
    PQDestroy(pq); 
    
    printf("PQ Test 4:\n");  
    pq = PQCreate(&CmpFunc, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    PQClear(pq);
    RUN_TEST(0 == PQSize(pq), "size");
 
    PQDestroy(pq); 
}

int main()
{   
    Test();
    return 0;
}
