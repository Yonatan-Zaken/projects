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

#include "linkedlist.h"
#include "recursion.h"

size_t IterFib(size_t position)
{
    size_t res = 1, prev = 0, next = 1;
    int i = 0;
    
    for (i = 1; i < position; i += 1)
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
    node_t *current = head, *prev = NULL;
    node_t *new_head = NULL;
    /*
    assert(NULL != head);
    */
    if (NULL == head->next->next)
    {
        current = current->next;
        head->next->next = head;       
        head->next = NULL;   
        return current;
    }    
    
    new_head = RecFlip(head->next);    
    head->next->next = current;       
    head->next = NULL;

    return new_head;
}

/*
stack_t *RecSortStack(stack_t *stack)
{



}
*/
