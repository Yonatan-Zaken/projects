/*********************************/
/*   			             	 */
/*   Recursion                   */
/*   Author: Yonatan Zaken       */
/*   Last Updated 14/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/
#include <string.h> /* strlen */
#include <assert.h> /* assert */

#include "stack.h"
#include "linkedlist.h"
#include "recursion.h"

size_t IterFib(size_t position)
{
    size_t res = 1, prev = 0, next = 1;
    size_t i = 0;
    
    for (i = 1; i < position; ++i)
    {
        res += prev;
        prev = next;
        next = res;
    }
   
    return res;
}

size_t RecFib(size_t position)
{
    if(0 == position || 1 == position)
    {
        return 1;
    }    
        
    return (RecFib(position - 2) + RecFib(position - 1));
}

size_t RecStrlen(const char *str)
{
    size_t size = 0;
    
    if ('\0' == *str)
    {
        return 0;
    }
    
    size = RecStrlen(str + 1) + 1;
    
    return size;
}

int RecStrcmp(const char *s1, const char *s2)
{
    int result = 0;
    
    if ((*s1 != *s2) || ('\0' == *s1))
    {
        return (*s1 - *s2);
    }
    
    result = RecStrcmp(s1 + 1, s2 + 1);
    return result;
}

char *RecStrcpy(char *dest, const char *src)
{
    if ('\0' != *src)
    {
        RecStrcpy(dest + 1, src + 1);
    }
    
    *dest = *src;
    return dest;
}

char *RecStrcat(char *dest, const char *src)
{
    if ('\0' != *dest)
    {
        RecStrcat(dest + 1, src);
    }
    
    else if ('\0' != (*dest = *src))
    {
        RecStrcat(dest + 1, src + 1);
    }
    
    return dest;
}


char *RecStrstr(const char *haystack, const char *needle)
{
    if (*haystack != *needle)
    {
        RecStrstr(haystack + 1, needle);
    }
    
    else if (*haystack == *needle)
    {
        RecStrstr(haystack + 1, needle + 1);
    }
    
}

node_t *RecFlip(node_t *head)
{
    node_t *new_head = NULL;
    
    if (NULL == head->next)
    {   
        return head;
    }    
    
    new_head = RecFlip(head->next);    
    head->next->next = head;       
    head->next = NULL;

    return new_head;
}


static void RecSortStack(stack_t *stack, void *data)
{
    int top_stack = 0;
    
    assert(NULL != stack);
    
    if (StackIsEmpty(stack))
    {
        return;
    }
    
    if (1 < StackSize(stack))
    {
        top_stack = *(int*)StackPeek(stack);
        StackPop(stack);
        RecSortStack(stack, (void*)&top_stack);
    }
    
    if (*(int *)data >= *(int *)StackPeek(stack))
    {
        StackPush(stack, data);
    }
    else
    {
        top_stack = *(int*)StackPeek(stack);
        StackPop(stack);
        StackPush(stack, data);
        RecSortStack(stack, (void*)&top_stack);
    }
    
    return;
}

void SortStack(stack_t *stack)
{
    assert(NULL != stack);
    RecSortStack(stack, StackPeek(stack));
}

