/*********************************/
/*   			             	 */
/*   Main file DS 2              */
/*   Yonatan Zaken		         */
/*   Last Updated 27/11/19       */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */
#include "stack.h" 

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
    
    RUN_TEST(8 == sizeof(stack1), "Check stack1 size\n");
    RUN_TEST(20 == (char*)stack1->end - (char*)stack1->start, "Check Stack\n");
    RUN_TEST((char*)stack1->current == (char*)stack1->start, "Check Stack\n");
    StackPop(stack1); /* pop before any push commited */
    RUN_TEST(NULL == StackPeek(stack1), "peek when stack is empty");
    RUN_TEST(1 == StackPush(stack1, pdata), "push return value");
    RUN_TEST(77 == *(int*)StackPeek(stack1), "peek on last value pushed");
    StackPop(stack1);
    RUN_TEST(stack1->current == stack1->start, "after first pop");
    
    StackDestroy(stack1);
} 

static void TestStack2()
{
    size_t element_size = sizeof(double);
    size_t capacity = 10;
    
    double data1 = 12.45;
    double data2 = 1.2;
    double data3 = 6.2;
    double data4 = 1.1;
    
    stack_t* stack1 = StackCreate(element_size, capacity);
    
    printf("Test second stack.\n");
    
    RUN_TEST(80 == (char*)stack1->end - (char*)stack1->start, "Check Stack\n");
    RUN_TEST(1 == StackPush(stack1, &data1), "push 1 second stack");
    RUN_TEST(1 == StackPush(stack1, &data2), "push 2 second stack");
    RUN_TEST(1 == StackPush(stack1, &data3), "push 3 second stack");
    RUN_TEST(1 == StackPush(stack1, &data4), "push 4 second stack");
    
    
    StackDestroy(stack2);
}   

static void TestStack3()
{


}



int main()
{
    TestStack1();   
    TestStack2();
    TestStack3();

    return 0;
}



















