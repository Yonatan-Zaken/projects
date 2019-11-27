/*********************************/
/*    Data Structures            */
/*    Stack                      */       
/*    Author :Guy Cohen Zedek    */
/*    Reviewed By:               */
/*    Date:     /11/2019         */
/*                               */
/*********************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

typedef struct Stack stack_t;

/* This function creates new Stack */
stack_t* StackCreate(size_t element_size, size_t capacity);

/* This function destroy the Stack */
void StackDestroy(stack_t* mystack);

/* This function push given element to the top of the Stack */
int StackPush(stack_t* mystack, const void* data);

/* This function pop the element that is on the top of the Stack and remove it */
void StackPop(stack_t* mystack);

/* This function checkes if the Stack is empty */
int StackIsEmpty(const stack_t* mystack);

/* This function return the number of elements in the stack */
size_t StackSize(const stack_t* mystack);

/* This function returns the top most elemet on the Stack */
void* StackPeek(const stack_t* mystack);

#endif
