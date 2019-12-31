#ifndef __DOUBLE_LINKED_LIST_H__
#define __DOUBLE_LINKED_LIST_H__

#include <stddef.h> /* size_t */

typedef struct DLLNode *iterator_t;
typedef struct DLL dll_t;

typedef int (*action_func_ptr)(void *node_data, void *user_data);
typedef int (*match_func_ptr)(void *node_data, void *user_data);

/**********************************************/
/* Returns pointer to the DLL data structure  */
/* complexity of malloc                       */
/**********************************************/
dll_t *DLLCreate();

/**************************************************/
/* Destroys the DLL data and frees it from memory */
/* Undefined behaviour when DLL is empty          */
/* complexity of free                             */
/**************************************************/
void DLLDestroy(dll_t *dll);

/*****************************************/
/* Gets an iterator                      */
/* Returns the next iterator             */
/* complexity O(1)                       */
/*****************************************/
iterator_t DLLGetNext(iterator_t it);

/*****************************************/
/* Gets a iterator                       */
/* Returns the pervious iterator         */
/* complexity O(1)                       */
/*****************************************/
iterator_t DLLGetPrev(iterator_t it);

/*********************************************************************/
/* Gets a pointer to a data structure, a iterator and a data pointer */
/* and inserts the iterator before the iterator sent by the user     */
/* complexity O(1)                                                   */
/*********************************************************************/    
iterator_t DLLInsert(dll_t *dll, iterator_t it, void *data);

/*********************************************************************/    
/* Removes the iterator sent to it and returns the iterator next     */
/* to the iterator that was removed                                  */
/* complexity O(1)                                                   */
/*********************************************************************/    
iterator_t DLLRemove(iterator_t it);

/***********************************************/
/* Checks if the DLL is empty                  */
/* returns 1 if its empty or 0 if not empty    */
/* complexity O(1)                             */
/***********************************************/
int DLLIsEmpty(const dll_t *dll);

/***********************************************/
/* Returns the size of the DLL                 */
/* complexity O(n)                             */
/***********************************************/
size_t DLLSize(const dll_t *dll);

/***********************************************/
/* Returns the first iterator after the head   */
/* complexity O(1)                             */
/***********************************************/
iterator_t DLLBegin(dll_t *dll);

/***********************************************/
/* Returns the iterator to the tail            */
/* complexity O(1)                             */
/***********************************************/
iterator_t DLLEnd(dll_t *dll);

/***********************************************/
/* Returns the data of the current iterator    */
/* complexity O(1)                             */
/***********************************************/
void *DLLGetData(iterator_t it);

/*********************************************************/
/* Returns 1 if the iterators are equal or 0 otherwise   */
/* complexity O(1)                                       */
/*********************************************************/
int DLLIsSameIter(const iterator_t it1, const iterator_t it2);

/****************************************************************/
/* Returns an iterator with the data sent to the function after */
/* adding it to the end of the data structure before the tail   */
/* If fails returns the tail iterator.                          */
/* complexity O(1)                                              */
/****************************************************************/
iterator_t DLLPushBack(dll_t *dll, void *data);

/***********************************************************************/
/* Removes the iterator that is before the tail of the data structure  */
/* and returns a pointer to the data that was removed                  */   
/* complexity O(1)                                                     */
/***********************************************************************/
void *DLLPopBack(dll_t *dll);

/****************************************************************/
/* Returns an iterator with the data sent to the function after */
/* adding it to the head of the data structure after the head   */
/* If fails returns the tail iterator.                          */
/* complexity O(1)                                              */
/****************************************************************/
iterator_t DLLPushFront(dll_t *dll, void *data);

/***********************************************************************/
/* Removes the iterator that is after the head of the data structure   */
/* and returns a pointer to the data that was removed                  */   
/* complexity O(1)                                                     */
/***********************************************************************/
void *DLLPopFront(dll_t *dll);

/***************************************************************************/
/* Returns a new list that contains the elements between the iterators     */
/* start and end. Start includes the head iterator and end doesn't include */ 
/* the tail iterator.                                                      */   
/* complexity O(1)                                                         */  
/***************************************************************************/    
iterator_t DLLSplice(iterator_t start, iterator_t end, iterator_t where);

/* what is behaviour when start = end */
/* a_ptr m_ptr names */
/********************************************************************/
/* Performs an action defined by a pointer to a function on all the */ 
/* iterators from the start to end not including the end.           */
/* return 0 if succeeds or 1 if fails                               */
/* complexity O(n)                                                  */
/********************************************************************/
int DLLForEach(iterator_t start, iterator_t end, action_func_ptr action, void *user_data);

/********************************************************************/
/* Traverse the list and returns the first iterator that matchs     */
/* a condition defined by the function from start to end not        */
/* including end.                                                   */
/* complexity O(n)                                                  */
/********************************************************************/
iterator_t DLLFind(iterator_t start, iterator_t end, match_func_ptr match, void *user_data);

#endif
