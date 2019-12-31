/*********************************/
/*   			             	 */
/*   Header file DS 5            */
/*   Yonatan Zaken		         */
/*   Last Updated 4/12/19        */
/*   Reviewed by: Itai           */   
/*			                   	 */
/*********************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct Queue queue_t;

/*******************************************/
/* Gets no paramaters and returns a queue  */
/* data structure with two dummies         */
/* complexity depends on malloc            */
/*******************************************/
queue_t *QCreate();

/***************************************************/
/* Gets a queue data structure Destroys it and     */
/* frees it from memory. complexity of SLLDestroy  */
/* frees it from memory. complexity O(n)           */
/* WARNING: Undefined if parameter is NULL pointer */
/***************************************************/
void QDestroy(queue_t *queue);

/******************************************************/
/* Enter a new item to the queue before rear. Return  */
/* 1 - failure, 0 - success. complexity is O(1).      */
/* WARNING: Undefined if parameter is NULL pointer    */
/******************************************************/
int QEnqueue(queue_t *queue, void *data);

/*************************************************************/
/* Pop out the item from front of queue. complexity is O(1)  */
/* WARNING: Undefined if parameter is NULL pointer           */
/*************************************************************/
void QDequeue(queue_t *queue);

/*********************************************************************/
/* Checks if queue contains any nodes not including dummies          */
/* If queue is empty returns 1, otherwise returns 0. complexity O(1) */
/* WARNING: Undefined if parameter is NULL pointer                   */
/*********************************************************************/
int QIsEmpty(const queue_t *queue);

/******************************************************************/
/* Returns the node that was first entered to the queue           */
/* Undefined behavior for peeking an empty queue. complexity O(1) */
/* WARNING: Undefined if parameter is NULL pointer                */
/******************************************************************/
void *QPeek(const queue_t *queue);

/*****************************************************/
/* Returns the queue size. Complexity O(n)           */
/* WARNING: Undefined if parameter is NULL pointer   */
/*****************************************************/
size_t QSize(const queue_t *queue);

/*****************************************************************/
/* Appends the second queue to the first queue. Complexity O(1)  */
/* WARNING: Undefined if parameter is NULL pointer               */
/*****************************************************************/
queue_t *QAppend(queue_t *queue1, queue_t *queue2);

#endif
