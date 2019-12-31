/*********************************/
/*   			             	 */
/*   Main file DS 5              */
/*   Yonatan Zaken		         */
/*   Last Updated 4/12/19        */
/*   Reviewed by: Itai           */   
/*			                   	 */
/*********************************/

#include <stdio.h>

#include "queue.h"
#include "linkedlist.h"

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


static void TestQueue1()
{
    int x1 = 77, x2 = 55, x3 = 99, x4 = 22;
    float y1 = 7.0, y2 = 5.0, y3 = 9.0, y4 = 2.0;    
    queue_t *new_queue = QCreate();
    queue_t *new_queue2 = QCreate();
    
    printf("Queue test 1:\n");
        
    RUN_TEST(0 == QEnqueue(new_queue, &x1), "Test1 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x2), "Test1 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x3), "Test1 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x4), "Test1 QEnqueue");
    
    RUN_TEST(0 == QIsEmpty(new_queue), "Test1 QIsEmpty")
    RUN_TEST(4 == QSize(new_queue), "Test Qsize")
    RUN_TEST(77 == *(int*)QPeek(new_queue), "Test1 QPeek");
    printf("peek 1 : %d\n", *(int*)QPeek(new_queue));
    QDequeue(new_queue);
    
    RUN_TEST(0 == QIsEmpty(new_queue), "Test1 QIsEmpty");
    RUN_TEST(3 == QSize(new_queue), "Test Qsize");
    RUN_TEST(55 == *(int*)QPeek(new_queue), "Test1 QPeek");
    printf("peek 1 : %d\n", *(int*)QPeek(new_queue));
    QDequeue(new_queue);
    
    RUN_TEST(0 == QIsEmpty(new_queue), "Test1 QIsEmpty");
    RUN_TEST(2 == QSize(new_queue), "Test Qsize");
    RUN_TEST(99 == *(int*)QPeek(new_queue), "Test1 QPeek");
    printf("peek 1 : %d\n", *(int*)QPeek(new_queue));
    QDequeue(new_queue);
    
    RUN_TEST(0 == QIsEmpty(new_queue), "Test1 QIsEmpty");
    RUN_TEST(1 == QSize(new_queue), "Test Qsize");
    RUN_TEST(22 == *(int*)QPeek(new_queue), "Test1 QPeek");
    printf("peek 1 : %d\n", *(int*)QPeek(new_queue));
    QDequeue(new_queue);
    RUN_TEST(1 == QIsEmpty(new_queue), "Test1 QIsEmpty");
    
    QDestroy(new_queue);
    
    printf("\nQueue test 2:\n");
    
    new_queue = QCreate();
    
    RUN_TEST(0 == QEnqueue(new_queue, &x1), "Test2 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x2), "Test2 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x3), "Test2 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x4), "Test2 QEnqueue");
        
    RUN_TEST(0 == QEnqueue(new_queue2, &y1), "Test2 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue2, &y2), "Test2 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue2, &y3), "Test2 QEnqueue");
    RUN_TEST(0 == QEnqueue(new_queue2, &y4), "Test2 QEnqueue");
    
    RUN_TEST(0 == QIsEmpty(new_queue2), "Test2 QIsEmpty");
    RUN_TEST(4 == QSize(new_queue2), "Test2 Qsize");
    RUN_TEST(7.0 == *(float*)QPeek(new_queue2), "Test2 QPeek");
    printf("peek 2 : %.2f\n", *(float*)QPeek(new_queue2));
    
    QAppend(new_queue, new_queue2);
    RUN_TEST(0 == QIsEmpty(new_queue), "Test2 QIsEmpty");
    RUN_TEST(8 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(77 == *(int*)QPeek(new_queue), "Test2 QPeek after append");
    printf("peek 2 : %d\n", *(int*)QPeek(new_queue));
    
    QDequeue(new_queue);
    RUN_TEST(7 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(55 == *(int*)QPeek(new_queue), "Test2 QPeek");
    QDequeue(new_queue);
    RUN_TEST(6 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(99 == *(int*)QPeek(new_queue), "Test2 QPeek");
    QDequeue(new_queue);
    RUN_TEST(5 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(22 == *(int*)QPeek(new_queue), "Test2 QPeek");
    QDequeue(new_queue);    
    RUN_TEST(4 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(7.0 == *(float*)QPeek(new_queue), "Test2 QPeek");
    QDequeue(new_queue);    
    RUN_TEST(3 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(5.0 == *(float*)QPeek(new_queue), "Test2 QPeek");
    QDequeue(new_queue);    
    RUN_TEST(2 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(9.0 == *(float*)QPeek(new_queue), "Test2 QPeek");
    QDequeue(new_queue);    
    RUN_TEST(1 == QSize(new_queue), "Test2 Qsize");
    RUN_TEST(2.0 == *(float*)QPeek(new_queue), "Test2 QPeek");
    QDequeue(new_queue);    
    RUN_TEST(0 == QSize(new_queue), "Test2 Qsize");
    
    QDestroy(new_queue);
    
    printf("\n");
}

int main()
{
    TestQueue1();
    
    return 0;
}
