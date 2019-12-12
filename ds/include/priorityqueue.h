#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include <stddef.h> 

typedef struct PQueue pq_t;

typedef int (*match_func_pq)(void*, void*);
typedef int (*compare_func_ptr)(const void*, const void*, void*);

/**********************************************/
/* Returns pointer to the PQ  data structure  */
/* complexity of malloc                       */
/**********************************************/
pq_t *PQCreate(compare_func_ptr cmp_ptr, void *param);

/*************************************************/
/* Destroys the PQ  datastructure and frees it   */
/* from memory                                   */
/* complexity of free                            */
/*************************************************/
void PQDestroy(pq_t *pq);

/*****************************************/
/* Gets the PQ structure and pops the    */
/* highest priority element              */
/* Returns the data removed              */
/* complexity O(1)                       */
/*****************************************/
void *PQDequeue(pq_t *pq);

/*****************************************/
/* Gets the PQ structure and             */
/* Returns the pervious iterator         */
/* complexity O(1)                       */
/*****************************************/
int PQEnqueue(pq_t *pq, void *data);

/*********************************************************************/
/* gets the data structure and returns the data wof the highest      */
/* priority element                                                  */
/* complexity O(1)                                                   */
/*********************************************************************/    
void *PQPeek(const pq_t *pq);

/*********************************************************************/    
/* gets the data structure and returns the number of elements        */                                           
/* complexity O(n)                                                   */
/*********************************************************************/    
size_t PQSize(const pq_t *pq);

/***********************************************/
/* Checks whether the data structure is empty  */
/* returns 1 if its empty or 0 if not empty    */
/* complexity O(1)                             */
/***********************************************/
int PQIsEmpty(const pq_t *pq);

/***********************************************/
/* gets the data structure and removes its     */
/* elements                                    */
/* complexity O(n)                             */
/***********************************************/
void PQClear(pq_t *pq);

/************************************************/
/* gets the data structure and a data to search,*/
/* once the element is found, its removed       */
/* complexity O(1)                              */
/************************************************/
void *PQErase(pq_t *pq, match_func_pq m_ptr, void *data);

#endif
