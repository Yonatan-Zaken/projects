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

#define NUM_OF_DUMMIES 2

struct Queue
{
    node_t *front;
    node_t *rear;
};

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
		    FREE(new_q->rear);
			return NULL;
		}
	}

	return new_q;  
}

void QDestroy(queue_t *queue)
{
    assert(NULL != queue);
    
	SLLDestroy(queue->front);
	FREE(queue);
}

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

void QDequeue(queue_t *queue)
{
    assert(NULL != queue);
    
	SLLRemoveAfter(queue->front);
}

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);

	return (queue->front->next == queue->rear);
}

void *QPeek(const queue_t *queue)
{
	assert (NULL != queue);

	return ((queue->front)->next)->data;
}

size_t QSize(const queue_t *queue)
{
	assert (NULL != queue);

	return (SLLSize(queue->front) - NUM_OF_DUMMIES);
}

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
