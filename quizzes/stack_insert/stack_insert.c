/*******************************************************/
/* Insert data to stack while keeping the contents of  */
/* the stack sorted without using a second stack       */
/*******************************************************/

#include <stdio.h>
#include <assert.h>

#include "stack.h"

#define NUM_OF_ELEMENTS 10

/*************************** Recursive stack insert *************************/

void RecStackInsert(stack_t *stack, int *data)
{
    int top_of_stack = 0;
    
    if (StackIsEmpty(stack))
    {
        StackPush(stack, data);
        return;
    }
    
    top_of_stack = *(int *)StackPeek(stack);
    
    if (*data >= top_of_stack)
    {
        StackPush(stack, data);
        return;
    }
    
    StackPop(stack);   
    RecStackInsert(stack, data);
    StackPush(stack, &top_of_stack);
}

void StackInsert(stack_t *stack, int *data)
{
    if (StackIsEmpty(stack))
    {
        StackPush(stack, data);
        return;
    }
    
    RecStackInsert(stack, data);
}

/******************************* Print stack *****************************/

void PrintStack(stack_t *stack)
{
    while (!StackIsEmpty(stack))
    {
        printf("%d\n", *(int*)StackPeek(stack));
        StackPop(stack);
    }
}

void TestStackInsert(stack_t *stack)
{
    int x1 = 1, x2 = 3, x3 = 5, x4 = 9, x5 = 2, x6 = 4, x7 = 0;
    
    StackInsert(stack, &x1);
    StackInsert(stack, &x2);
    StackInsert(stack, &x3);
    StackInsert(stack, &x4);
    StackInsert(stack, &x5);
    StackInsert(stack, &x6);
    StackInsert(stack, &x7);
    
    PrintStack(stack); 
}

int main (int argc, char *argv[])
{
    stack_t *stack = StackCreate(sizeof(int), NUM_OF_ELEMENTS);
    if (NULL == stack)
    {
        return 1;
    }
    
    TestStackInsert(stack);
    StackDestroy(stack);
    
	return 0;
}

