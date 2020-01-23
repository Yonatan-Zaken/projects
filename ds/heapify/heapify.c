/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   AVL Tree                    */
/*   Author: Yonatan Zaken       */
/*   Last Updated 23/1/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "priorityqueue.h"
#include "vector.h"
#include "heapify.h"

#define CAPACITY 1
#define ROOT 1
#define SUCCESS 0
#define FAIL 1
#define ELEMENT_SIZE sizeof(void *)

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

int WrapCompare(const void *data1, const void *data2, void *param)
{
    return (*(int*)data1 - *(int*)data2);
}

pq_t *PQCreate(compare_func_ptr cmp, void *param)
{     
    pq_t *pq = malloc(sizeof(*pq));
    if (NULL != pq)
    {
        pq->heap = VectorCreate(sizeof(void *), CAPACITY);
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
    void *root_holder = NULL;
    void *end_holder = NULL;
    void *temp_holder = NULL;
    size_t last_index = 0;
    
    assert(NULL != pq);
    
    last_index = VectorSize(pq->heap);
    end_holder = VectorGetItemAddress(pq->heap, last_index);
    root_holder = VectorGetItemAddress(pq->heap, ROOT);
    temp_holder = memcpy(temp_holder, root_holder, ELEMENT_SIZE);
    memcpy(root_holder, end_holder, ELEMENT_SIZE);
    temp_holder = memcpy(end_holder, temp_holder, ELEMENT_SIZE);
    
    HeapifyDown(pq->heap, last_index, ROOT, ELEMENT_SIZE, pq->wrap.cmp_func, 
                                                            pq->wrap.param);
                                                            
    VectorPopBack(pq->heap);
    
    return temp_holder;
}

int PQEnqueue(pq_t *pq, void *data)
{
    size_t element_size = 0;
    
    assert(NULL != pq);
     
    if (0 == VectorPushBack(pq->heap, &data))
    {
        HeapifyUp(pq->heap, VectorSize(pq->heap), VectorSize(pq->heap), 
                      ELEMENT_SIZE, pq->wrap.cmp_func, pq->wrap.param);
        
        return SUCCESS;        
    }
    
    return FAIL;
}

void *PQPeek(const pq_t *pq)
{
    void **peek_data = NULL;
    
    assert(NULL != pq);
    
    peek_data = VectorGetItemAddress(pq->heap, ROOT);
    
    return *peek_data;
}
   
size_t PQSize(const pq_t *pq)
{
    assert(NULL != pq);
    
    return VectorSize(pq->heap);
}

int PQIsEmpty(const pq_t *pq)
{
    assert(NULL != pq);
    
    return (0 == VectorSize(pq->heap));  
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
    size_t size = 0;    
    
    assert(NULL != pq->heap);
    
           
}

void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size,
                                       compare_func_ptr cmp, void *param)
{
    void **new_data = NULL;
    void **vector_data = NULL;    
    size_t parent_index = (size - 1) / 2;
    
    assert(NULL != arr);
    
    new_data = VectorGetItemAddress(arr, size); 
    vector_data = VectorGetItemAddress(arr, parent_index);
    
    while (0 != parent_index)
    {
        Swap(*new_data, *vector_data);
        vector_data = VectorGetItemAddress(arr, (size/2));
        0 < cmp(*new_data, *vector_data, param)       
    }
    
    
}                                              
                                             
void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size,
                                         compare_func_ptr cmp, void *param)
{

}               
               
               
