#include <stdlib.h>    /* malloc */
#include <string.h>    /* memcpy */
#include <assert.h>    /* assert */
#include <stddef.h>    /* offsetof */

#include "circularbuffer.h" 

#define MIN_SIZE 1

struct CBuffer
{
    size_t read_index;
    size_t write_index;
    size_t capacity;
    int arr[MIN_SIZE];
};

cbuffer_t *CBufferCreate(size_t capacity)
{
    cbuffer_t *newbuffer = (cbuffer_t *)malloc(offsetof(cbuffer_t, arr) 
                                           + (sizeof(int) * capacity));
    if (NULL != newbuffer)
    {
        newbuffer->read_index = 0;
        newbuffer->write_index = 0;
        newbuffer->capacity = capacity;
        
        return newbuffer;
    }
    
    return NULL;
}

void CBufferDestroy(cbuffer_t *cb)
{
    assert(NULL != cb);
    
    free(cb); cb = NULL;
}

void CBufferWrite(cbuffer_t *cb, int data)
{
    assert(NULL != cb);
    
    cb->arr[cb->write_index] = data;
    cb->write_index = (cb->write_index + 1) % cb->capacity;      
}

int CBufferRead(cbuffer_t *cb)
{
    int read_value = 0;
    
    assert(NULL != cb);
    
    read_value = cb->arr[cb->read_index];
    cb->read_index = (cb->read_index + 1) % cb->capacity;
    
    return read_value;
}

size_t CBufferCapacity(const cbuffer_t *cb)
{
    assert(NULL != cb);
    
    return cb->capacity;
}
