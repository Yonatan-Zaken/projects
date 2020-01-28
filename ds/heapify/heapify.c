/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Heap                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 23/1/20        */
/*   Reviewed by: Israel         */   
/*			                   	 */
/*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "priorityqueue.h"
#include "vector.h"
#include "heapify.h"

#define CAPACITY 4
#define ROOT 1
#define SUCCESS 0
#define FAIL 1
#define ELEMENT_SIZE sizeof(void *)

#define UNUSED(x) (void)(x)

typedef struct Wrapper
{
    compare_func_ptr cmp_func;
    void *param;
} wrap_t;

struct PQueue
{
    vector_t *heap;
    wrap_t wrap;    
};

int WrapCmp(void **data2, void **data1, void *param)
{
    return (((wrap_t *)param)->cmp_func(*data1, *data2, ((wrap_t *)param)->param));
}

pq_t *PQCreate(compare_func_ptr cmp, void *param)
{     
    pq_t *pq = malloc(sizeof(*pq));
    if (NULL != pq)
    {
        pq->heap = VectorCreate(ELEMENT_SIZE, CAPACITY);
        if (NULL == pq->heap)
        {
            free(pq); pq = NULL;
            return pq;
        }
        pq->wrap.cmp_func = cmp;
        pq->wrap.param = param;
    }
    return pq;
}

void PQDestroy(pq_t *pq)
{
    assert(NULL != pq);
    
    VectorDestroy(pq->heap);
    free(pq); pq = NULL;
}

static void Swap(void **ptr1, void **ptr2)
{
    void *temp = *ptr2;
    *ptr2 = *ptr1;
    *ptr1 = temp;
}

void *PQDequeue(pq_t *pq)
{
    void **root_holder = NULL;
    void **end_holder = NULL;
    void *return_value = NULL;
    
    size_t last_index = 0;
    
    assert(NULL != pq);
    
    last_index = VectorSize(pq->heap);
    end_holder = VectorGetItemAddress(pq->heap, last_index); 
    root_holder = VectorGetItemAddress(pq->heap, ROOT);
    
    Swap(root_holder, end_holder);
    return_value = *end_holder;
    VectorPopBack(pq->heap);
    
    HeapifyDown(pq->heap, last_index - 1, ROOT, ELEMENT_SIZE,
                               pq->wrap.cmp_func, &pq->wrap);    
    return return_value;
}

int PQEnqueue(pq_t *pq, void *data)
{
    assert(NULL != pq);
     
    if (SUCCESS == VectorPushBack(pq->heap, &data))
    {
        HeapifyUp(pq->heap, VectorSize(pq->heap), VectorSize(pq->heap), 
                           ELEMENT_SIZE, pq->wrap.cmp_func, &pq->wrap);
        
        return SUCCESS;        
    }
    
    return FAIL;
}

void *PQPeek(const pq_t *pq)
{
    assert(NULL != pq);
    
    return *(void **)VectorGetItemAddress(pq->heap, ROOT);
}
   
size_t PQSize(const pq_t *pq)
{
    assert(NULL != pq);
    
    return VectorSize(pq->heap);
}

int PQIsEmpty(const pq_t *pq)
{
    assert(NULL != pq);
    
    return (SUCCESS == VectorSize(pq->heap));  
}

void PQClear(pq_t *pq)
{
    size_t size = 0;
    
    assert(NULL != pq);
    
    size = PQSize(pq);
    
    while (0 < size)
    {
        VectorPopBack(pq->heap);
        --size;
    }   
}

void *PQErase(pq_t *pq, match_func_pq match, void *data)
{
    size_t index = ROOT;    
    size_t size = 0;
    void **last = NULL;
    void **current = NULL;
    
    assert(NULL != pq->heap);
    
    size = VectorSize(pq->heap);
    last = VectorGetItemAddress(pq->heap, size);
    
    for (; index <= size; ++index)
    {
        current = VectorGetItemAddress(pq->heap, index);
        if (1 == match(*current, data))
        {
            Swap(current, last);
            VectorPopBack(pq->heap);
            HeapifyUp(pq->heap, size - 1, index, ELEMENT_SIZE, pq->wrap.cmp_func,
                                                                      &pq->wrap);
            HeapifyDown(pq->heap, size - 1, index, ELEMENT_SIZE, pq->wrap.cmp_func,
                                                                        &pq->wrap);
            return *last;
        } 
    }
    return NULL;          
}

void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size,
                                       compare_func_ptr cmp, void *param)
{    
    void **new_data = NULL;
    void **vector_data = NULL;    
    size_t parent_index = index / 2;
 
    UNUSED(index);
    UNUSED(element_size);
    UNUSED(cmp);
   
    assert(NULL != arr);
    
    new_data = VectorGetItemAddress(arr, size); 
    vector_data = VectorGetItemAddress(arr, parent_index);
    
    while (0 != parent_index)
    {
        if (0 < WrapCmp(new_data, vector_data, (wrap_t *)param))
        {
            Swap(new_data, vector_data);
            new_data = VectorGetItemAddress(arr, parent_index);
            parent_index /= 2;
            vector_data = VectorGetItemAddress(arr, parent_index);
        }
        else
        {
            break;
        }       
    }  
}                                              

void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size,
                                         compare_func_ptr cmp, void *param)
{
    size_t left_index = index * 2;
    size_t right_index = (index * 2) + 1;
    size_t biggest = 0;
    void **parent = NULL;
    
    UNUSED(cmp);
    UNUSED(element_size);
    
    assert(NULL != arr);
    
    parent = VectorGetItemAddress(arr, index);
    
    while (left_index <= size)
    {
        if ((0 < WrapCmp(VectorGetItemAddress(arr, left_index), parent,
                                                     (wrap_t *)param)))
        {
            biggest = left_index;
        }
        else
        {
            biggest = index;
        }
        
        if ((right_index <= size) && 
           (0 < WrapCmp(VectorGetItemAddress(arr, right_index),
                VectorGetItemAddress(arr, biggest), (wrap_t *)param)))
        {
            biggest = right_index;
        }
        
        if (biggest != index)
        {
            Swap(parent, VectorGetItemAddress(arr, biggest));
            index = biggest;
            left_index = index * 2;
            right_index = (index * 2) + 1;
            parent = VectorGetItemAddress(arr, index);
        }
        
        else
        {
            break;
        }
    }
}               

