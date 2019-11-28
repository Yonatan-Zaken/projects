/*********************************/
/*   			             	 */
/*   Main file DS 2              */
/*   Yonatan Zaken		         */
/*   Last Updated 28/11/19       */
/*   Reviewed by: Daniel         */   
/*			                   	 */
/*********************************/

#include <stdio.h>   /* printf */
#include <string.h>  /* strcpy, strcmp */
#include <stdlib.h>  /* malloc */
#include "stack.h"   /* stack data structure functions */

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

struct Stack
{
    void* start;
    void* current;
    void* end;
    size_t element_size;
};

static void TestStack1()
{
    size_t element_size = sizeof(int);
    size_t capacity = 5;
    int data = 77;
    int *pdata = &data; 
    stack_t* stack1 = StackCreate(element_size, capacity);
    
    printf("Test for first stack.\n");
    
    RUN_TEST(8 == sizeof(stack1), "check stack1 size\n");
    RUN_TEST(20 == (char*)stack1->end - (char*)stack1->start, "check Stack1\n");
    RUN_TEST((char*)stack1->current == (char*)stack1->start, "check Stack1\n");
    StackPop(stack1); /* pop before any push commited */
    RUN_TEST(NULL == StackPeek(stack1), "peek when stack1 is empty");
    RUN_TEST(1 == StackPush(stack1, pdata), "push return value stack1");
    RUN_TEST(77 == *(int*)StackPeek(stack1), "peek last value pushed stack1");
    StackPop(stack1);
    RUN_TEST(stack1->current == stack1->start, "after first pop stack1");
    
    StackDestroy(stack1); 
    printf("\n");
} 

static void TestStack2()
{
    size_t element_size = sizeof(double);
    size_t capacity = 4;
    double data1 = 12.45;
    double data2 = 1.2;
    double data3 = 6.2;
    double data4 = 1.1;
    stack_t* stack2 = StackCreate(element_size, capacity);
        
    printf("Test second stack.\n");
    
    RUN_TEST(32 == (char*)stack2->end - (char*)stack2->start, "Check Stack2\n");
    RUN_TEST(1 == StackPush(stack2, &data1), "push 1 stack2");
    RUN_TEST(12.45 == *(double*)StackPeek(stack2), "peek value pushed stack2");
    RUN_TEST(1 == StackPush(stack2, &data2), "push 2 stack2");
    RUN_TEST(1.2 == *(double*)StackPeek(stack2), "peek value pushed stack2");
    RUN_TEST(1 == StackPush(stack2, &data3), "push 3 stack2");
    RUN_TEST(6.2 == *(double*)StackPeek(stack2), "peek value pushed stack2");
    RUN_TEST(1 == StackPush(stack2, &data4), "push 4 stack2");
    RUN_TEST(1.1 == *(double*)StackPeek(stack2), "peek value pushed stack2");
    RUN_TEST(4 == StackSize(stack2), "check stack 2 size when full");
    RUN_TEST(0 == StackPush(stack2, &data1), "push 5 stack2 when full");
    RUN_TEST(0 == StackPush(stack2, &data1), "push 6 stack2 when full");
    
    RUN_TEST(1.1 == *(double*)StackPeek(stack2), "peek value stack2");
    StackPop(stack2);
    RUN_TEST(6.2 == *(double*)StackPeek(stack2), "peek value stack2");
    StackPop(stack2);
    RUN_TEST(1.2 == *(double*)StackPeek(stack2), "peek value stack2");
    StackPop(stack2);
    RUN_TEST(12.45 == *(double*)StackPeek(stack2), "peek value stack2");
    StackPop(stack2);
    RUN_TEST(1 == StackIsEmpty(stack2), "stack 2 is empty?");
    RUN_TEST(NULL == StackPeek(stack2), "stack 2 peek when empty");
    
    
    StackDestroy(stack2);
    printf("\n");
}   

static void TestStack3()
{
    size_t element_size = sizeof(char*);
    size_t capacity = 3;    
    stack_t* stack3 = StackCreate(element_size, capacity);
    char *str1 = (char*)malloc(sizeof(char) * 5);
    char *str2 = (char*)malloc(sizeof(char) * 4);
    char *str3 = (char*)malloc(sizeof(char) * 7);
    
    printf("Test third stack.\n");
    strcpy(str1, "abcd");
    strcpy(str2, "TTT");
    strcpy(str3, "QQQAAA");
    
    RUN_TEST(24 == (char*)stack3->end - (char*)stack3->start, "Check Stack3");
    RUN_TEST(1 == StackPush(stack3, str1), "push 1 stack3");
    RUN_TEST(0 == strcmp(str1, (char*)StackPeek(stack3)),
    "peek last value pushed");
    RUN_TEST(1 == StackPush(stack3, str2), "push 2 stack3");
    RUN_TEST(0 == strcmp(str2, (char*)StackPeek(stack3)),
    "peek last value pushed");
    RUN_TEST(1 == StackPush(stack3, str2), "push 3 stack3");
    RUN_TEST(0 == strcmp(str2, (char*)StackPeek(stack3)),
                               "peek last value pushed");

    free(str1); str1 = NULL;
    free(str2); str2 = NULL;
    free(str3); str3 = NULL;
    
    StackDestroy(stack3);
    printf("\n");
}


int main()
{
    TestStack1();   
    TestStack2();
    TestStack3();

    return 0;
}



















