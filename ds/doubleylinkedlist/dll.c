/*********************************/
/*   			             	 */
/*   Implementing file DS 7      */
/*   Yonatan Zaken		         */
/*   Last Updated 9/12/19        */
/*   Reviewed by: Itai           */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dllist.h" /* doubley linked list functions */

#define FREE(ptr) {free(ptr); ptr = NULL;}

struct DLLNode
{
    void *data;
    struct DLLNode *next;
    struct DLLNode *prev;
};

typedef struct DLLNode node_t;

struct DLL
{
    struct DLLNode head;
    struct DLLNode tail;
};

dll_t *DLLCreate()
{
    dll_t *new_dll = (dll_t *)malloc(sizeof(dll_t));
    if (NULL == new_dll)
    {
        return NULL;
    }           
   
    new_dll->head.next = &new_dll->tail;
    new_dll->head.prev = NULL;
    new_dll->tail.next = NULL;
    new_dll->tail.prev = &new_dll->head;
    new_dll->head.data = NULL;
    new_dll->tail.data = NULL;
    
    return new_dll;
}

void DLLDestroy(dll_t *dll)
{
    node_t *runner = NULL;    
    node_t *current = NULL;
    
    assert (NULL != dll);    
    
    runner = dll->head.next;    
    current = dll->head.next;
    
    while (runner != &dll->tail)   
    {
        runner = runner->next;
        FREE(current);
        current = runner;
    }
    
    FREE(dll);
}

iterator_t DLLGetNext(iterator_t it)
{
    iterator_t iter = NULL;

    assert(NULL != it);
    
    iter = it->next;
    
    return iter;
}

iterator_t DLLGetPrev(iterator_t it)
{
    iterator_t iter = NULL;

    assert(NULL != it);
    
    iter = it->prev;
    
    return iter;
}

iterator_t DLLInsert(dll_t *dll, iterator_t it, void *data)
{
    node_t *new_node = NULL;
    
    assert(NULL != dll);
    assert(NULL != data);
    assert(NULL != it);
       
    new_node = (node_t *)malloc(sizeof(node_t));
    if (NULL == new_node)
    {   
        it = DLLEnd(dll);
        return it;
    }
    
    new_node->data = data;
    
    new_node->next = it;
    new_node->prev = it->prev;
    (it->prev)->next = new_node;
    it->prev = new_node;
    
    it = new_node;
    
    return it;
}

iterator_t DLLRemove(iterator_t it)
{
    node_t *temp = NULL;
    
    assert(NULL != it);
    
    temp = it;
    
    (it->prev)->next = it->next;
    (it->next)->prev = it->prev;
    it = it->next;
    
    FREE(temp);
    
    return it;
}

int DLLIsEmpty(const dll_t *dll)
{
    assert(NULL != dll);
    
    return (dll->head.next == &dll->tail);
}

size_t DLLSize(const dll_t *dll)
{
    node_t *runner = NULL;
    size_t counter = 0;
    
    assert(NULL != dll);
    
    runner = dll->head.next;
    
    while (runner != &dll->tail)
    {
        runner = runner->next;
        ++counter;
    }
    
    return counter;
}

/* const dll */
iterator_t DLLBegin(dll_t *dll)
{
    iterator_t it = NULL;
    
    assert(NULL != dll);
    
    it = dll->head.next;
    
    return it;  
}

/* const dll */
iterator_t DLLEnd(dll_t *dll)
{
    iterator_t it;
    
    assert(NULL != dll);
    
    it = &dll->tail;
    
    return it;
}

void *DLLGetData(iterator_t it)
{
    assert(NULL != it);
    
    return it->data;
}

int DLLIsSameIter(const iterator_t it1, const iterator_t it2)
{
    assert(NULL != it1);
    assert(NULL != it2);
    
    return (it1 == it2);
}

/* dll->t instead of call for DLLEnd */ 
iterator_t DLLPushBack(dll_t *dll, void *data)
{
    assert(NULL != dll);
    assert(NULL != data);
    
    return DLLInsert(dll, DLLEnd(dll), data);
}

/* dll->tail->prev instead of call to functions */
void *DLLPopBack(dll_t *dll)
{
    iterator_t it = NULL;
    void *temp = NULL;
    
    assert(NULL != dll);
    
    it = DLLGetPrev(DLLEnd(dll));
    temp = DLLGetData(it);    
        
    it = DLLRemove(it);
    
    return temp;
}

iterator_t DLLPushFront(dll_t *dll, void *data)
{
    assert(NULL != dll);         
    assert(NULL != data);
    
    return DLLInsert(dll, DLLBegin(dll), data);
}

void *DLLPopFront(dll_t *dll)
{
    iterator_t it;
    void *temp = NULL;
    
    assert(NULL != dll);
    
    it = DLLBegin(dll);
    temp = DLLGetData(it);
    
    it = DLLRemove(it);
    
    return temp;
}

iterator_t DLLSplice(iterator_t start, iterator_t end, iterator_t where)
{
    assert(NULL != start);
    assert(NULL != end);
    assert(NULL != where);
    
    where->next->prev = end->prev;
    end->prev->next = where->next;
    where->next = start;
    
    start->prev->next = end;
    end->prev = start->prev;
    start->prev = where;
    
    return where;   
}

int DLLForEach(iterator_t start, iterator_t end, action_func_ptr action, void *user_data)
{
    iterator_t i = NULL;
    int return_val = 0;
    
    assert(NULL != start);
    assert(NULL != end);
    assert(NULL != action);
    
    for (i = start; i != end; i = DLLGetNext(i))
    {
        if (0 != (return_val = action(i->data, user_data)))
        {
            return return_val;
        }
    }
    
    return return_val;
}

iterator_t DLLFind(iterator_t start, iterator_t end, match_func_ptr match, void *user_data)
{
    iterator_t i = NULL;
    
    assert(NULL != start);
    assert(NULL != end);
    assert(NULL != match);
    assert(NULL != user_data);
    
    for (i = start; i != end; i = DLLGetNext(i))
    {
        if (1 == match(i->data, user_data))
        {
            return i;
        }
    }
    
    return end;
}
