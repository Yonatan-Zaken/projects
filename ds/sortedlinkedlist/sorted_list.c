/*********************************/
/*   			             	 */
/*   Implementing file DS 8      */
/*   Itai Marienberg	         */
/*   Last Updated 10/12/19       */
/*              */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "sortedlist.h" /* sorted linked list functions */
#include "dllist.h" /* doubley linked list functions */

#define FREE(ptr) free(ptr); ptr = NULL;

#define UNUSED(x) (void)(x)

typedef struct my_struct
{
    void *user_data;
    void *param;
    is_before func;
}my_struct_t;

struct SLL
{
    dll_t *list;
    my_struct_t my_struct;
};

sll_t *SortLLCreate(is_before func, void *param)
{
    sll_t *new_sll = NULL;
    
    assert(NULL != func);
    
    new_sll = (sll_t *)malloc(sizeof(sll_t));
    if (NULL != new_sll)
    {
        new_sll->list = DLLCreate();
        if (NULL == new_sll->list)
        {
            FREE(new_sll);
            return NULL;
        }
    }
    else return NULL;
    
    new_sll->my_struct.func = func;
    new_sll->my_struct.param = param;
    
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
    
    end = SLLEnd(sll);
    
    for (i = SLLBegin(sll); 1 != SLLIsSameIter(i, end); i = SLLNext(i))
    {
        if (1 == sll->my_struct.func(SLLGetData(i), data, sll->my_struct.param))
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

static int MyIsBefore(void *data, void* data_struct)
{
    return ((my_struct_t *)data_struct)->func(data, ((my_struct_t *)data_struct)->user_data, ((my_struct_t *)data_struct)->param);
}

sll_iterator_t SLLFind(const sll_t *sll, const void *data, sll_iterator_t start, sll_iterator_t end)
{
    sll_iterator_t it;
    sll_t *sll1 = NULL;
    
    assert(NULL != sll);
    
    sll1 = (sll_t *)sll;
    sll1->my_struct.user_data = (void*)data;
    
    it.current = DLLFind(start.current, end.current, 
                 &MyIsBefore, &sll1->my_struct); 
                                                                  
    it = SLLPrev(it);
    
    if (0 == (sll1->my_struct.func(data, SLLGetData(it), sll1->my_struct.param)))
    {
        return it;
    }
    
    return end;                                         
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

    sll_iterator_t src_start = SLLBegin(src);
	sll_iterator_t src_end = SLLBegin(src);
	sll_iterator_t dest_current = SLLBegin(dest);
	
	sll_iterator_t src_tail = SLLEnd(src);
	sll_iterator_t dest_tail = SLLEnd(dest);

	assert(NULL != dest);
	assert(NULL != src);

	while (!(SLLIsSameIter(dest_current, dest_tail))
	         && !(SLLIsSameIter(src_end, src_tail)))
	{
		while (!(SLLIsSameIter(dest_current, dest_tail)) &&
		       !(dest->my_struct.func(SLLGetData(dest_current), 
		       SLLGetData(src_end), dest->my_struct.param)))
		{	
				dest_current = SLLNext(dest_current);	
		}
		
		if((SLLIsSameIter(dest_current, dest_tail)))
		{
			break;
		}
		
		while (!(SLLIsSameIter(src_end, src_tail)) &&
		       !(dest->my_struct.func(SLLGetData(src_end),
		       SLLGetData(dest_current), dest->my_struct.param)))
		{	
				src_end = SLLNext(src_end);		
		}

		DLLSplice(src_start.current, src_end.current,
		           DLLGetPrev(dest_current.current));
		dest_current = SLLNext(dest_current);
		src_start = src_end;
	}

	if(SLLIsSameIter(dest_current, dest_tail))
	{
		src_end = src_tail;
		DLLSplice(src_start.current, src_end.current,
		           DLLGetPrev(dest_current.current));
	}
}
