/*********************************/
/*   			             	 */
/*   Implementing file DS 3      */
/*   Yonatan Zaken		         */
/*   Last Updated 1/12/19        */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert null check */
#include <string.h> /* memcpy */

#include "vector.h" /* dynamic vector data structure */

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 4

struct Vector
{
    void *start;
    size_t size;
    size_t capacity;
    size_t element_size; 
};

vector_t* VectorCreate(size_t element_size, size_t capacity)
{
    vector_t *myvector = (vector_t*)malloc(sizeof(vector_t));
    if (NULL != myvector)
    {   
        myvector->start = (void*)malloc(element_size * capacity);    
        if (NULL == myvector->start)
        {
            return NULL;
        }
        
        myvector->capacity = capacity;
        myvector->element_size = element_size;
        myvector->size = 0;
    }
   
    return myvector;
}

/* This function destroys the vector */
/* Warning: the function doesn't get NULL pointer */
void VectorDestroy(vector_t *myvector)
{
    assert(NULL != myvector);
    
    free(myvector->start); myvector->start = NULL;
    free(myvector); myvector = NULL;    
}

/* This function push new item at the end of the vector */
/* 0 - success , 1- failure */
/* Warning: Could resize the capacity in an unpredictable manner */
/* Warning: the function doesn't get NULL pointer */
int VectorPushBack(vector_t *myvector, const void *data)
{
    assert(NULL != myvector);
    assert(NULL != data);
    
    if (myvector->size == myvector->capacity)
    {
        if (1 == VectorReserve(myvector, myvector->capacity * GROWTH_FACTOR))
        {   
            return 1;
        } 
    }

    memcpy((char*)myvector->start + (myvector->element_size) *
             (myvector->size), data, myvector->element_size);
                 
    ++(myvector->size);
        
    return 0;       
}

/* This function pops the last item in the vector */
/* Warning: the function doesn't get NULL pointer */
void VectorPopBack(vector_t *myvector)
{
    assert(NULL != myvector);
    
    if (0 != myvector->size)
    {
        --(myvector->size);
        
        if (myvector->size == (myvector->capacity / SHRINK_FACTOR))
        {
            VectorReserve(myvector, (myvector->capacity / GROWTH_FACTOR));
        }
    }  
}

/* This function resizing the vector size as needed with extra space */
/* 0 - success , 1- failure */
/* Warning: the function doesn't get NULL pointer */
int VectorReserve(vector_t *myvector, size_t new_capacity)
{
    assert(NULL != myvector);
    
    myvector->capacity = new_capacity;
    myvector->start = (void*)realloc(myvector->start, 
                      (myvector->capacity) * (myvector->element_size));
                    
    if (NULL == myvector->start)
    {
        return 1;
    }
    
    return 0;   
}

/* This function return the total size of the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorCapacity(const vector_t *myvector)
{
    assert(NULL != myvector);
    
    return myvector->capacity;
}

/* This function return the current number of elements in the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorSize(const vector_t *myvector)
{
    assert(NULL != myvector);
    
    return myvector->size;
}

/* This function return specific item address to the user */
/* Warning: the address is valid until using PopBack/PushBack over the limit */
/* Warning: the function doesn't get NULL pointer */
void *VectorGetItemAddress(const vector_t *myvector, size_t position)
{
    assert(NULL != myvector);
    
    if (position == 0 || position > myvector->size)
    {
        return NULL;
    }
    
    return ((char*)myvector->start + (position - 1) * (myvector->element_size));
}
