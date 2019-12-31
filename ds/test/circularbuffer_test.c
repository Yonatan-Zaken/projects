/*********************************/
/*   			             	 */
/*   Main file DS 6              */
/*   Yonatan Zaken		         */
/*   Last Updated 5/12/19        */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stdio.h>

#include "circularbuffer.h"

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

static void CircularBufferTest1()
{
    char buffer[] = "abcdefghijklmnopqrstuvwxyz";
    char buffer2[5];
    char buffer3[] = "0000000";
    char buffer4[10];
    char buffer5[10];
    cbuffer_t *cb1 = NULL;
    
    printf("Circular Buffer Test1:\n");
    
    cb1 = CBufferCreate(10);
    RUN_TEST(NULL != cb1, "create test1"); 
    RUN_TEST(6 == CBufferWrite(cb1, buffer, 6), "write test1");
    RUN_TEST(10 == CBufferCapacity(cb1), "capacity test1");
    RUN_TEST(0 == CBufferIsEmpty(cb1), "is empty test1");
    RUN_TEST(4 == CBufferFreeSpace(cb1), "free space test1");
    
    CBufferDestroy(cb1);
    
    printf("\nCircular Buffer Test2:\n");
    
    cb1 = CBufferCreate(10);
    RUN_TEST(10 == CBufferWrite(cb1, buffer, 15), "write test2");
    RUN_TEST(0 == CBufferIsEmpty(cb1), "is empty test2");
    RUN_TEST(5 == CBufferRead(cb1, buffer2, 5), "read test2");
    printf("%s\n", buffer2);
    RUN_TEST(5 == CBufferFreeSpace(cb1), "free space test2");
    RUN_TEST(5 == CBufferWrite(cb1, buffer3, 7), "write test2");  
    RUN_TEST(10 == CBufferRead(cb1, buffer4, 13), "read test2");
    RUN_TEST('f' == buffer4[0], "buffer4 test");
    RUN_TEST('g' == buffer4[1], "buffer4 test");
    RUN_TEST('0' == buffer4[5], "buffer4 test");
    RUN_TEST(1 == CBufferIsEmpty(cb1), "is empty test2");
    RUN_TEST(-1 == CBufferRead(cb1, buffer2, 4), "read test2");        
    
    CBufferDestroy(cb1); 
    
    printf("\nCircular Buffer Test3:\n");
    
    cb1 = CBufferCreate(10);
    RUN_TEST(4 == CBufferWrite(cb1, buffer, 4), "write test3");
    RUN_TEST(4 == CBufferRead(cb1, buffer2, 4), "read test3");
    RUN_TEST(3 == CBufferWrite(cb1, buffer, 3), "write test3");
    RUN_TEST(7 == CBufferFreeSpace(cb1), "free space test3");
    RUN_TEST(7 == CBufferWrite(cb1, buffer, 15), "write test3");
    RUN_TEST(0 == CBufferFreeSpace(cb1), "free space test3");
    RUN_TEST(10 == CBufferRead(cb1, buffer5, 18), "read test3");
    RUN_TEST('a' == buffer5[0], "buffer5 test");
    RUN_TEST('g' == buffer5[9], "buffer5 test");
    RUN_TEST(1 == CBufferIsEmpty(cb1), "is empty test");
    
    CBufferDestroy(cb1);
            
    printf("\n");
}

int main()
{
    CircularBufferTest1();
    
    return 0;
}
