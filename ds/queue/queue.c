/*********************************/
/*   			             	 */
/*   Implementing file DS 5      */
/*   Yonatan Zaken		         */
/*   Last Updated 4/12/19        */
/*   Reviewed by: Itai           */   
/*			                   	 */
/*********************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert */

#include "queue.h" /* queue functions */
#include "linkedlist.h" /* singley linkedlist functions */

#define FREE(ptr) free(ptr); ptr = NULL;

struct Queue
{
    node_t *front;
    node_t *rear;
};

/* Creates new queue */
queue_t *QCreate()
{
	queue_t *new_q = (queue_t *)malloc(sizeof(queue_t)); 
	if (NULL == new_q)
	{
	    return NULL;
	}

	new_q->rear = SLLCreateNode(NULL, NULL);
	if (NULL != new_q->rear)
	{
		new_q->front = SLLCreateNode(new_q->rear, NULL);
		if (NULL == new_q->front)
		{
		    FREE(new_q);
			return NULL;
		}
	}

	return new_q;  
}

/* Destroys the data structure */
/* WARNING: Doesnt get NULL pointer */
void QDestroy(queue_t *queue)
{
    assert(NULL != queue);
    
	SLLDestroy(queue->front);
	FREE(queue);
}

/* Enter a new item to the queue */
/* WARNING: Doesnt get NULL pointer */
int QEnqueue(queue_t *queue, void *data)
{
    node_t *new_node = NULL;
    
    assert(NULL != queue);
    assert(NULL != data);
        
	new_node = SLLCreateNode(NULL, data);
	if (NULL == new_node)
	{
		return 1;
	}

	SLLInsert(new_node, queue->rear);

	queue->rear = new_node;

	return 0;
}

/* Get out the front item */
/* WARNING: Doesnt get NULL pointer */
void QDequeue(queue_t *queue)
{
    assert(NULL != queue);
    
	SLLRemoveAfter(queue->front);
}

/* If empty returns 1, otherwise returns 0 */
/* WARNING: Doesnt get NULL pointer */
int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);

	return (queue->front->next == queue->rear);
}

/* Returns the front item */
/* WARNING: Doesnt get NULL pointer */
void *QPeek(const queue_t *queue)
{
	assert (NULL != queue);

	return ((queue->front)->next)->data;
}

/* Returns the queue size */
/* WARNING: Doesnt get NULL pointer */
size_t QSize(const queue_t *queue)
{
	assert (NULL != queue);

	return (SLLSize(queue->front->next)-1);
}

/* Appends the second queue to the first queue */
/* WARNING: Doesnt get NULL pointer */
queue_t *QAppend(queue_t *queue1, queue_t *queue2)
{
	assert(NULL != queue2);
	assert(NULL != queue1);
	
	queue1->rear->next = queue2->front;

	SLLRemove(queue1->rear);
	SLLRemove(queue1->rear);
	
	queue1->rear = queue2->rear;
	
	FREE(queue2);
	
	return queue1;
}
