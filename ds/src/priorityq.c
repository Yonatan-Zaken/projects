/*********************************/
/*   			             	 */
/*   Implementing file DS 9      */
/*   Yonatan Zaken		         */
/*   Last Updated 11/12/19       */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*********************************/

#include <stddef.h>    /* size_t */
#include <stdlib.h>    /* malloc */
#include <assert.h>    /* assert */

#include "sortedlist.h" /* sorted list functions */
#include "priorityqueue.h" /* priority list functions */
 
#define FREE(ptr) {free(ptr); ptr = NULL;}

typedef struct Wrapper
{
    compare_func_ptr cmp_func;
    void *param;
}wrap_t;

struct PQueue
{
    sll_t *queue;
    wrap_t wrap;    
};

int MyCompare(const void *node_data, const void *user_data, void *param)
{
    return (0 < ((wrap_t *)param)->cmp_func(node_data, 
                                             user_data, 
                                             ((wrap_t *)param)->param));
} 

pq_t *PQCreate(compare_func_ptr cmp_func, void *param)
{
    pq_t *new_pq = (pq_t *)malloc(sizeof(pq_t));
    if(NULL != new_pq)
    {
        new_pq->queue = SortLLCreate(&MyCompare, &new_pq->wrap);
        if (NULL != new_pq->queue)
        {
            new_pq->wrap.cmp_func = cmp_func;
            new_pq->wrap.param = param;
            
            return new_pq;
        }
        
        FREE(new_pq);
        return NULL;
    }
    
    return NULL;
}

void PQDestroy(pq_t *pq)
{
    assert(NULL != pq);
       
    SortLLDestroy(pq->queue);
    FREE(pq);
}

void *PQDequeue(pq_t *pq)
{
    assert(NULL != pq);
    
    return SLLPopFront(pq->queue);
}

int PQEnqueue(pq_t *pq, void *data)
{
    assert(NULL != pq);
    
    return (SLLIsSameIter(SortLLInsert(pq->queue, data), SLLEnd(pq->queue)));
}

void *PQPeek(const pq_t *pq)
{
    assert(NULL != pq);
    
    return SLLGetData(SLLBegin(pq->queue));
}

size_t PQSize(const pq_t *pq)
{
    assert(NULL != pq);
    
    return SLLSize(pq->queue);
}

int PQIsEmpty(const pq_t *pq)
{
    assert(NULL != pq);
    
    return SLLIsEmpty(pq->queue);
}

void PQClear(pq_t *pq)
{ 
    assert(NULL != pq);
   
    while (!PQIsEmpty(pq))
    {
        PQDequeue(pq);
    }
}

void *PQErase(pq_t *pq, match_func_pq m_ptr, void *data)
{   
    sll_iterator_t it;
    void *temp = NULL;
    
    assert(NULL != pq);
    
    it = (SLLFindBy(pq->queue, SLLBegin(pq->queue),
                  SLLEnd(pq->queue), m_ptr, data));
     
    temp = SLLGetData(it);
    if (SLLIsSameIter(it, SLLEnd(pq->queue)))
    {
        return NULL;
    }
    
    SortLLRemove(it);
    return temp;
}
