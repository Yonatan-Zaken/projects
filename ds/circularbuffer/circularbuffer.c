/*********************************/
/*   			             	 */
/*   Implementing file DS 6      */
/*   Yonatan Zaken		         */
/*   Last Updated 5/12/19        */
/*   Reviewed by: Daniel         */   
/*			                   	 */
/*********************************/

#include <stdlib.h>    /* malloc */
#include <string.h>    /* memcpy */
#include <assert.h>    /* assert */
#include <stddef.h>    /* offsetof */

#include "circularbuffer.h" /* circular buffer functions */

#define MIN_SIZE 1

struct CBuffer
{
    size_t read_index;
    size_t size;
    size_t capacity;
    char arr[1];
};

cbuffer_t *CBufferCreate(size_t capacity)
{
    cbuffer_t *newbuffer = (cbuffer_t *)malloc(offsetof(cbuffer_t, arr) 
                                                            + capacity);
    if (NULL != newbuffer)
    {
        newbuffer->read_index = 0;
        newbuffer->size = 0;
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

ssize_t CBufferRead(cbuffer_t *cb , void *buffer, size_t count)
{
    int temp = count;
    char *runner = NULL;
    size_t to_read_till_end = 0;
    
    assert(NULL != cb);
    assert(NULL != buffer);
    
    to_read_till_end = cb->capacity - cb->read_index;
    runner = buffer;
    
    if (1 == CBufferIsEmpty(cb))
    {
        return -1;
    }
    
    else if (count > cb->size)
    {
        count = cb->size;
        temp = count;
    }
    
    if (cb->read_index + count > cb->capacity)
    {
        memcpy(runner, &cb->arr[cb->read_index], to_read_till_end);
        cb->size -= to_read_till_end;   
        runner += to_read_till_end;
        count -= to_read_till_end;
        cb->read_index = 0;
    } 
    
    memcpy(runner, &cb->arr[cb->read_index], count);
    cb->read_index = count;
    cb->size -= count;
    
    return temp;
}

ssize_t CBufferWrite(cbuffer_t *cb, const void *buffer, size_t count)
{
    const char *runner = NULL;
    size_t write_index = 0;
    size_t temp = count;
    size_t to_write_till_end = 0;
    
    assert(NULL != cb);
    assert(NULL != buffer);
    
    write_index = (cb->read_index + cb->size) % cb->capacity;
    to_write_till_end = cb->capacity - write_index;
    runner = buffer;
        
    if (count > CBufferFreeSpace(cb))
    {
        count = CBufferFreeSpace(cb);
        temp = count;
    }        
    
    if (write_index + count > cb->capacity)
    {
        memcpy(&cb->arr[write_index], runner, to_write_till_end);
        cb->size += to_write_till_end;      
        runner += to_write_till_end;
        count -= to_write_till_end;
        write_index = 0;
    }
    
    memcpy(&cb->arr[write_index], runner, count);
    cb->size += count;
    
    return temp;
}

int CBufferIsEmpty(const cbuffer_t *cb)
{
    assert(NULL != cb);
    
    return (0UL == cb->size); 
}

size_t CBufferCapacity(const cbuffer_t *cb)
{
    assert(NULL != cb);
    
    return cb->capacity;
}

size_t CBufferFreeSpace(const cbuffer_t *cb)
{
    assert(NULL != cb);
    
    return (cb->capacity - cb->size);
}
