#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <sys/types.h> /* ssize_t and size_t */

typedef struct CBuffer cbuffer_t;

/****************************************************/
/* Creates new Circular Buffer.                     */
/* Gets number of bytes of the circular buffer.     */
/* complexity: O(1)                                 */
/****************************************************/
cbuffer_t *CBufferCreate(size_t capacity);

/**********************************/
/* Destroys the data structure.   */
/* Gets the circular buffer.      */
/* Not defined for NULL pointer.  */
/* complexity: O(1)               */
/**********************************/
void CBufferDestroy(cbuffer_t *cb);

/*****************************************************************/
/* Copy 'count' bytes from circular buffer to 'buffer'.          */
/* Returns the number of bytes read if succeed, or -1 if fails.  */
/* Gets the circular buffer, the target buffer and the number of */
/* bytes to read.                                                */
/* Undefined behaviour if count is bigger than user buffer size  */
/* Not defined for NULL pointer.                                 */
/* complexity of memcpy                                         */
/*****************************************************************/
ssize_t CBufferRead(cbuffer_t *cb , void *buffer, size_t count);

/********************************************************************/
/* Copy 'count' bytes from 'buffer' to circular buffer.             */
/* Returns the number of write bytes.                               */
/* Gets target circular buffer, the source buffer and the number of */
/* bytes to write.                                                  */
/* Not defined for NULL pointer.                                    */
/* complexity of memcpy                                            */  
/********************************************************************/
ssize_t CBufferWrite(cbuffer_t *cb ,const void *buffer, size_t count);

/***************************************************************/
/* If circular buffer is empty returns 1, otherwise returns 0. */
/* Gets the circular buffer                                    */
/* Not defined for NULL pointer.                               */
/* complexity: O(1)                                            */
/***************************************************************/   
int CBufferIsEmpty(const cbuffer_t *cb);

/*************************************************/
/* Return the total size of the circular buffer. */
/* Gets the circular buffer.                     */
/* Not defined for NULL pointer.                 */
/* complexity: O(1)                              */
/*************************************************/
size_t CBufferCapacity(const cbuffer_t *cb);

/*******************************************************/
/* Returns the unwritten bytes in the circular buffer. */
/* Gets the circular buffer.                           */
/* Not defined for NULL pointer.                       */
/* complexity: O(1)                                    */
/*******************************************************/
size_t CBufferFreeSpace(const cbuffer_t *cb);

#endif
