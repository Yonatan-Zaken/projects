/*********************************/
/*   			             	 */
/*   Header file DS 5            */
/*   Yonatan Zaken		         */
/*   Last Updated 4/12/19        */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct Queue queue_t;

/* Creates new queue */
queue_t *QCreate();

/* Destroys the data structure */
/* WARNING: Doesnt get NULL pointer */
void QDestroy(queue_t *queue);

/* Enter a new item to the queue */
/* WARNING: Doesnt get NULL pointer */
int QEnqueue(queue_t *queue, void *data);

/* Get out the front item */
/* WARNING: Doesnt get NULL pointer */
void QDequeue(queue_t *queue);

/* If empty returns 1, otherwise returns 0 */
/* WARNING: Doesnt get NULL pointer */
int QIsEmpty(const queue_t *queue);

/* Returns the front item */
/* WARNING: Doesnt get NULL pointer */
void *QPeek(const queue_t *queue);

/* Returns the queue size */
/* WARNING: Doesnt get NULL pointer */
size_t QSize(const queue_t *queue);

/* Appends the second queue to the first queue */
/* WARNING: Doesnt get NULL pointer */
queue_t *QAppend(queue_t *queue1, queue_t *queue2);

#endif
