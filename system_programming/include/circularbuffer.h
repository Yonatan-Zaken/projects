#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stddef.h> 

typedef struct CBuffer cbuffer_t;

cbuffer_t *CBufferCreate(size_t capacity);

void CBufferDestroy(cbuffer_t *cb);

int CBufferRead(cbuffer_t *cb);

void CBufferWrite(cbuffer_t *cb , int data);
  
size_t CBufferCapacity(const cbuffer_t *cb);

#endif
