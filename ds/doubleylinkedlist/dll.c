/*********************************/
/*   			             	 */
/*   Implementing file DS 6      */
/*   Yonatan Zaken		         */
/*   Last Updated 7/12/19        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dllist.h" /* doubley linked list functions */

#define FREE(ptr) free(ptr); ptr = NULL;

struct DLLNode
{
    void *data;
    struct DLLNode *next;
    struct DLLNode *prev;
};

typedef struct DLLNode node_t;

struct Iterator
{
    struct DLLNode *node;
};

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
    
    while (runner->next != &dll->tail)   
    {
        runner = runner->next;
        FREE(current);
        current = runner;
    }
    FREE(runner);
    FREE(dll);
}

iterator_t DLLGetNext(iterator_t it)
{
    iterator_t iter;
    iter.node = it.node->next;
    
    return iter;
}

iterator_t DLLGetPrev(iterator_t it)
{
    iterator_t iter;
    iter.node = it.node->prev;
    
    return iter;
}

iterator_t DLLInsert(dll_t *dll, iterator_t it, void *data)
{
    node_t *new_node = NULL;
    
    assert(NULL != dll);
    assert(NULL != data);
    
    new_node = (node_t *)malloc(sizeof(node_t));
    if (NULL == new_node)
    {   
        it.node = &dll->tail;
        return it;
    }
    
    new_node->data = data;
    
    new_node->next = it.node;
    new_node->prev = it.node->prev;
    (it.node->prev)->next = new_node;
    it.node->prev = new_node;
    
    it.node = new_node;
    
    return it;
}

iterator_t DLLRemove(iterator_t it)
{
    node_t *temp = it.node;
    
    (it.node->prev)->next = it.node->next;
    (it.node->next)->prev = it.node->prev;
    it.node = it.node->next;
    
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
    ++counter;
    
    while (runner->next != &dll->tail)
    {
        runner = runner->next;
        ++counter;
    }
    
    return counter;
}

iterator_t DLLBegin(dll_t *dll)
{
    iterator_t it;
    
    assert(NULL != dll);
    
    it.node = dll->head.next;
    
    return it;  
}

iterator_t DLLEnd(dll_t *dll)
{
    iterator_t it;
    
    assert(NULL != dll);
    
    it.node = &dll->tail;
    
    return it;
}

void *DLLGetData(iterator_t it)
{
    return it.node->data;
}

int DLLIsSameIter(const iterator_t it1, const iterator_t it2)
{
    return (it1.node == it2.node);
}

iterator_t DLLPushBack(dll_t *dll, void *data)
{
    assert(NULL != dll);
    assert(NULL != data);
    
    return DLLInsert(dll, DLLEnd(dll), &data);
}

void *DLLPopBack(dll_t *dll)
{
    iterator_t it;
    void *temp = NULL;
    
    assert(NULL != dll);
    
    it = DLLGetPrev(DLLEnd(dll));
    temp = DLLGetData(it);    
        
    it = DLLRemove(it);
    
    return temp;
}

iterator_t DLLPushFront(dll_t *dll, void *data)
{
  
    
}

void *DLLPopFront(dll_t *dll)
{

}

iterator_t DLLSplice(iterator_t start, iterator_t end, iterator_t where)
{

}

int DLLForEach(iterator_t start, iterator_t end, action_func_ptr a_ptr, void *ap)
{

}

iterator_t DLLFind(iterator_t start, iterator_t end, match_func_ptr m_ptr, void *ap)
{

}









