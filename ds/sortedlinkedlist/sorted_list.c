/*********************************/
/*   			             	 */
/*   Implementing file DS 8      */
/*   Yonatan Zaken		         */
/*   Last Updated 10/12/19       */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "sortedlist.h" /* sorted linked list functions */
#include "dllist.h" /* doubley linked list functions */

#define FREE(ptr) free(ptr); ptr = NULL;

#define UNUSED(x) (void)(x)

struct SLL
{
    dll_t *list;
    is_before func;
    void *param;
};

sll_t *SortLLCreate(is_before func, void *param)
{
    sll_t *new_sll = NULL;
    
    assert(NULL != func);
    
    new_sll = (sll_t *)malloc(sizeof(sll_t));
    if (NULL == new_sll)
    {
        return NULL;
    }
    
    new_sll->list = DLLCreate();
    new_sll->func = func;
    new_sll->param = param;
    
    return new_sll;
}

void SortLLDestroy(sll_t *sll)
{
    assert(NULL != sll);    
    
    DLLDestroy(sll->list);
    
    FREE(sll);
}

sll_iterator_t SortLLInsert(sll_t *sll, void *data)
{
    sll_iterator_t i;
    sll_iterator_t end;
    
    assert(NULL != sll);
    assert(NULL != data);
    
    end = SLLEnd(sll);
     
    for (i = SLLBegin(sll); 1 != SLLIsSameIter(i, end); i = SLLNext(i))
    {
        if (1 == sll->func(SLLGetData(i), data, sll->param))
        {
            break;
        }
    }
    
    i.current = DLLInsert(sll->list, i.current, data);
    return i;
}

sll_iterator_t SortLLRemove(sll_iterator_t it)
{
    it.current = DLLRemove(it.current);
    return (it);     
}

int SLLIsEmpty(const sll_t *sll)
{   
    assert(NULL != sll);
    
    return DLLIsEmpty(sll->list);
}

size_t SLLSize(const sll_t *sll)
{
    assert(NULL != sll);
    
    return DLLSize(sll->list);
}

sll_iterator_t SLLBegin(sll_t *sll)
{
    sll_iterator_t sll_it;
    
    assert(NULL != sll);
    
    sll_it.current = DLLBegin(sll->list);
    
    return sll_it;
}

sll_iterator_t SLLEnd(sll_t *sll)
{
    sll_iterator_t sll_it;
    
    assert(NULL != sll);
    
    sll_it.current = DLLEnd(sll->list);
    
    return sll_it;
}

sll_iterator_t SLLNext(sll_iterator_t it)
{
    it.current = DLLGetNext(it.current);
    return it;
}

sll_iterator_t SLLPrev(sll_iterator_t it)
{
    it.current = DLLGetPrev(it.current);
    return it;    
}

void *SLLGetData(sll_iterator_t it)
{
    return DLLGetData(it.current);
}

int SLLIsSameIter(const sll_iterator_t it1, const sll_iterator_t it2)
{
    return (DLLIsSameIter(it1.current, it2.current));
}

void* SLLPopBack(sll_t *sll)
{
    assert(NULL != sll);
    
    return DLLPopBack(sll->list);    
}

void* SLLPopFront(sll_t *sll)
{
    assert(NULL != sll);
    
    return DLLPopFront(sll->list); 
}

int SLLForEach(sll_iterator_t start, sll_iterator_t end, action_func_ptr a_ptr, void *ap)
{
    return DLLForEach(start.current, end.current, a_ptr, ap);     
}

sll_iterator_t SLLFind(const sll_t *sll, const void *data, sll_iterator_t start, sll_iterator_t end)
{
    sll_iterator_t it;
    
    assert(NULL != sll);
    
    it.current = DLLFind(start.current, end.current, (match_func_ptr)sll->func, 
                                                                  (void*)data);
    
    return it;                                                
}

sll_iterator_t SLLFindBy(const sll_t *sll, sll_iterator_t start , sll_iterator_t end, match_func_ptr m_ptr, const void *data)
{
    sll_iterator_t it;
    
    UNUSED(sll);
    
    assert(NULL != sll);
    
    it.current = DLLFind(start.current, end.current, m_ptr, (void*)data);
   
    return it;
}

void SLLMerge(sll_t *dest, sll_t *src)
{

}

