#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dlinkedlist.h" /* doubley linked list functions */

#define FREE(ptr){\
                    free(ptr); ptr = NULL;\
                 }

node_t *DLLCreateNode(node_t *previous, node_t *next, const void *data)
{
    node_t *newnode = NULL;
    
    newnode = (node_t *)malloc(sizeof(node_t));
    if (NULL == newnode)
    {
        return NULL;
    }

    newnode->data = (void *)data;
    newnode->next = next;
    new_node->previous = previous;
    
    return newnode;
}

void *DLLDestroy(node_t *node)
{
    node_t *runner = NULL;
    
    assert(NULL != node);
    
    while (NULL != runner)
    {
        runner = node->next;
        FREE(node);
        node = runner;
    }  
}

void DLLRemove(node_t *node)
{    
    assert(NULL != node);    
 
    (node->previous)->next = node->next;
    (node->next)->previous = node->previous;
    FREE(node);      
}

















