/*********************************/
/*   			             	 */
/*   Implementing file DS 2      */
/*   Yonatan Zaken		         */
/*   Last Updated 28/11/19       */
/*   Reviewed by: Daniel         */   
/*			                   	 */
/*********************************/

#include <stdlib.h>  /* malloc */
#include <assert.h>  /* assert checks for validity of input */
#include <string.h>  /* memcpy */
#include <stdio.h>   /* printf */
#include "stack.h"   /* stack data structure functions */

struct Stack
{
    void* start;
    void* current;
    void* end;
    size_t element_size;
};

/***********************************/
/* This function creates new Stack */
/***********************************/

stack_t* StackCreate(size_t element_size, size_t capacity)
{
    stack_t *stack_ptr = (stack_t*)malloc(sizeof(stack_t));
    if (NULL == stack_ptr)
    {
        return NULL;
    }
    
    stack_ptr->start = (void*)malloc(element_size * capacity);
    if (NULL == stack_ptr->start)
    {
        return NULL;
    } 
    
    stack_ptr->element_size = element_size;
    stack_ptr->current = (stack_ptr -> start);
    stack_ptr->end = (char*)(stack_ptr->start) + (element_size * capacity);
    
    return stack_ptr;
}

/***********************************/
/* This function destroy the Stack */
/***********************************/

void StackDestroy(stack_t* mystack)
{
    assert(NULL != mystack);
    
    free(mystack->start); mystack->start = NULL;
    free(mystack); mystack = NULL;
}

/************************************************************/
/* This function push given element to the top of the Stack */
/************************************************************/

int StackPush(stack_t* mystack, const void* data)
{
	assert(NULL != mystack);
	assert(NULL != data);

	if (mystack->current == mystack->end)
	{
		printf("Stack is full.\n");
		return 0;
	}

	memcpy(mystack->current, data, mystack->element_size);
	mystack->current = (char*)mystack->current + mystack->element_size;
    
	return 1;   
}

/******************************************************************************/
/* This function pop the element thats on the top of the Stack and removes it */
/******************************************************************************/

void StackPop(stack_t* mystack)
{
	assert(NULL != mystack);

	if(mystack->current != mystack->start)
	{
		mystack->current = (char*)mystack->current - mystack->element_size;
	}
	
	else
	{
		printf("Stack is empty.\n");
	}	
}

/***********************************************/
/* This function checkes if the Stack is empty */
/***********************************************/

int StackIsEmpty(const stack_t* mystack)
{
	assert(NULL != mystack);

	if (mystack->current == mystack -> start)
	{
		return 1;
	}

	return 0;    
}

/************************************************************/
/* This function return the number of elements in the stack */
/************************************************************/

size_t StackSize(const stack_t* mystack)
{
	assert(NULL != mystack);

	return (((char*)mystack->current - 
	         (char*)mystack->start) / (mystack->element_size));                
}

/**********************************************************/
/* This function returns the top most elemet on the Stack */
/**********************************************************/

void* StackPeek(const stack_t* mystack)
{
	assert(NULL != mystack);

	if (mystack->current == mystack->start)
	{
		printf("Stack is empty.\n");
		return NULL;
	}
    
	return ((char*)mystack->current - mystack->element_size);
}





















