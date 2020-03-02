/********************************/
/* Sort the contents of a stack */
/********************************/

#include <stdio.h>
#include <assert.h>

#include "stack.h"

#define NUM_OF_ELEMENTS 10

/************************* Stack Insert (sorted) **************************/

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

/****************************** Sort Stack ******************************/

void RecStackSort(stack_t *stack)
{
    int top_of_stack = 0;
    
    if (StackIsEmpty(stack))
    {
        return;
    }
    
    top_of_stack = *(int*)StackPeek(stack);
    StackPop(stack);
    RecStackSort(stack);
    StackInsert(stack, &top_of_stack);
}

void StackSort(stack_t *stack)
{
    assert(NULL != stack);
    
    RecStackSort(stack);
}

/****************************** Print Stack ******************************/

void PrintStack(stack_t *stack)
{
    while (!StackIsEmpty(stack))
    {
        printf("%d ", *(int*)StackPeek(stack));
        StackPop(stack);
    }
}

/****************************** Initialize Stack ******************************/

void InitStack(stack_t *stack)
{
    int x1 = 1, x2 = 5, x3 = 3, x4 = 9, x5 = 2, x6 = 4, x7 = 0;
    
    StackPush(stack, &x1);
    StackPush(stack, &x2);
    StackPush(stack, &x3);
    StackPush(stack, &x4);
    StackPush(stack, &x5);
    StackPush(stack, &x6);
    StackPush(stack, &x7);

}

int main ()
{
    stack_t *stack = StackCreate(sizeof(int), NUM_OF_ELEMENTS);
    if (NULL == stack)
    {
        return 1;
    }
    
    InitStack(stack);
    printf("Before Sort: ");
    PrintStack(stack);
    InitStack(stack);
    StackSort(stack);
    printf("\nAfter Sort: ");
    PrintStack(stack);
    printf("\n");
    StackDestroy(stack);
    
    return 0;
}
