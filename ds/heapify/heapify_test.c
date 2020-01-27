/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Heap                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 23/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "priorityqueue.h"
#include "heapify.h"

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

int IsMatch(void *data1, void *data2)
{
    return (*(int*)data1 == *(int*)data2);
}

int CompareFunc(const void *data1, const void *data2, void *param)
{
    UNUSED(param);
    
    return (*(int*)data1 - *(int*)data2);
}

static void Test1()
{
    pq_t *pq = NULL;

    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 4;

    printf("PQ Test 1:\n");  
    pq = PQCreate(&CompareFunc, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(3 == *(int *)PQPeek(pq), "peek");
    RUN_TEST(3 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(2 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(2 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(1 == *(int *)PQDequeue(pq), "Dequeue");
    PQDestroy(pq);
    
    printf("PQ Test 2:\n");  
    pq = PQCreate(&CompareFunc, NULL);
    RUN_TEST(0 == PQSize(pq), "size");
    RUN_TEST(1 == PQIsEmpty(pq), "size");
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(1 == PQSize(pq), "size");

    PQDestroy(pq); 
    
    printf("PQ Test 3:\n");  
    pq = PQCreate(&CompareFunc, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(2 == *(int*)PQErase(pq, &IsMatch, &x2), "erase");
    RUN_TEST(3 == PQSize(pq), "size");
    RUN_TEST(NULL == PQErase(pq, &IsMatch, &x4), "erase");
 
    PQDestroy(pq); 
    
    printf("PQ Test 4:\n");  
    pq = PQCreate(&CompareFunc, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    PQClear(pq);
    RUN_TEST(0 == PQSize(pq), "size");
 
    PQDestroy(pq);
    printf("\n\n"); 
}

static void Test2()
{
    pq_t *pq = NULL;

    int x1 = 10, x2 = 7, x3 = 5, x4 = 5, x5 = 2, x6 = 1, x7 = 3, x8 = 4, x9 = 2,
    x10 = 15;

    printf("PQ Test 5:\n\n");
    
    pq = PQCreate(&CompareFunc, NULL);
    printf("PQEnqueue:\n");          
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x4), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x5), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x6), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x7), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x8), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x9), "enqueue");
    printf("PQSize:\n");          
    RUN_TEST(9 == PQSize(pq), "size");
    
    printf("PQErase:\n");              
    RUN_TEST(7 == *(int*)PQErase(pq, &IsMatch, &x2), "erase");
    RUN_TEST(8 == PQSize(pq), "size");
    RUN_TEST(1 == *(int*)PQErase(pq, &IsMatch, &x6), "erase");
    RUN_TEST(7 == PQSize(pq), "size");
    RUN_TEST(NULL == PQErase(pq, &IsMatch, &x10), "erase");
    
    RUN_TEST(0 == PQEnqueue(pq, &x10), "enqueue");
    printf("PQPeek:\n");              
    RUN_TEST(15 == *(int *)PQPeek(pq), "peek");    
    RUN_TEST(8 == PQSize(pq), "size");

    RUN_TEST(5 == *(int*)PQErase(pq, &IsMatch, &x3), "erase");
    RUN_TEST(7 == PQSize(pq), "size");
    RUN_TEST(10 == *(int*)PQErase(pq, &IsMatch, &x1), "erase");
    RUN_TEST(6 == PQSize(pq), "size");
    
    
    PQDestroy(pq);
    printf("\n\n");
}

static void Test3()
{
    pq_t *pq = NULL;

    int x1 = 15, x2 = 10, x3 = 14, x4 = 9, x5 = 7, x6 = 13;

    printf("PQ Test :\n\n");
    
    pq = PQCreate(&CompareFunc, NULL);
    printf("PQEnqueue:\n");          
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x4), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x5), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x6), "enqueue");
    
    printf("PQSize:\n");          
    RUN_TEST(6 == PQSize(pq), "size");
    
    printf("PQErase:\n");              
    RUN_TEST(7 == *(int*)PQErase(pq, &IsMatch, &x5), "erase");
    RUN_TEST(5 == PQSize(pq), "size");
      
    
    PQDestroy(pq);
    printf("\n\n");
}


int main()
{   
    Test1();
    Test2();
    Test3();
    
    return 0;
}
