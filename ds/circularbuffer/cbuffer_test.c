/*********************************/
/*    Data Structures            */
/*    Circular Buffer            */       
/*    Author : Guy Cohen Zedek   */
/*    Reviewed By:               */
/*    Date: 5/12/2019            */
/*                               */
/*********************************/

#include <stdio.h> /* printf */

#include "circularbuffer.h" /* API function */

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
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

static void TestCBufferCreate()
{
    char buffer[] = "abcdefghijklmnopqrstuvwxyz";
    char buffer2[10];
    cbuffer_t * cb = CBufferCreate(5);
    printf("Circular Buffer 1:\n");
    RUN_TEST(4 == CBufferWrite(cb, buffer, 4));
    RUN_TEST(0 == CBufferIsEmpty(cb));
    RUN_TEST(1 == CBufferFreeSpace(cb));

    CBufferDestroy(cb);
    
    printf("\nCircular Buffer 2:\n");
    cb = CBufferCreate(15);
    
    RUN_TEST(15 == CBufferWrite(cb, buffer, 16));
    RUN_TEST(0 == CBufferIsEmpty(cb));
    RUN_TEST(0 == CBufferFreeSpace(cb));
    RUN_TEST(4 == CBufferRead(cb, buffer2, 4));
    RUN_TEST('a' == buffer2[0]);
    
    CBufferDestroy(cb);
    
    printf("\nCircular Buffer 3:\n");
    cb = CBufferCreate(15);
    
    RUN_TEST(15 == CBufferWrite(cb, buffer, 16));
    RUN_TEST(0 == CBufferIsEmpty(cb));
    RUN_TEST(0 == CBufferFreeSpace(cb));
    RUN_TEST(4 == CBufferRead(cb, buffer2, 4));
    RUN_TEST(4 == CBufferFreeSpace(cb));
    RUN_TEST(4 == CBufferWrite(cb, buffer, 6));
    RUN_TEST(0 == CBufferFreeSpace(cb));
    RUN_TEST('a' == buffer2[0]);
    
    CBufferDestroy(cb);
    
    printf("\nCircular Buffer 4:\n");
    cb = CBufferCreate(2);
    
    RUN_TEST(2 == CBufferWrite(cb, buffer, 16));
    RUN_TEST(0 == CBufferIsEmpty(cb));
    RUN_TEST(0 == CBufferFreeSpace(cb));
    RUN_TEST(2 == CBufferRead(cb, buffer2, 4));
    RUN_TEST(2 == CBufferFreeSpace(cb));
    RUN_TEST(2 == CBufferWrite(cb, buffer, 6));
    RUN_TEST(0 == CBufferFreeSpace(cb));
    RUN_TEST('b' == buffer2[1]);

    CBufferDestroy(cb);
    
    printf("\nCircular Buffer 5:\n");
    cb = CBufferCreate(10);
    
    RUN_TEST(6 == CBufferWrite(cb, buffer, 6));
    RUN_TEST(0 == CBufferIsEmpty(cb));
    RUN_TEST(4 == CBufferFreeSpace(cb));
    RUN_TEST(2 == CBufferRead(cb, buffer2, 2));
    RUN_TEST(6 == CBufferFreeSpace(cb));
    RUN_TEST(6 == CBufferWrite(cb, buffer, 8));
    RUN_TEST(0 == CBufferFreeSpace(cb));
    RUN_TEST('b' == buffer2[1]);

    CBufferDestroy(cb);
    
}

int main()
{
    TestCBufferCreate();
    return 0;
}
