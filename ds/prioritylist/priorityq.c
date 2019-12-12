/*********************************/
/*   			             	 */
/*   Implementing file DS 9      */
/*   Yonatan Zaken		         */
/*   Last Updated 11/12/19       */
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/

#include <stddef.h>    /* size_t */
#include "sortedlist.h" /* sorted list functions */
#include "priorityqueue.h" /* priority list functions */

struct PQueue
{
    sll_t *queue;
    compare_func_ptr cmp_ptr;
    void *param;    
};

pq_t *PQCreate(compare_func_ptr cmp_ptr, void *param)
{
    
}

void PQDestroy(pq_t *pq)
{

}

void *PQDequeue(pq_t *pq)
{

}

int PQEnqueue(pq_t *pq)
{

}

void *PQPeek(const pq_t *pq)
{

}

size_t PQSize(const pq_t *pq)
{

}

int PQIsEmpty(const pq_t *pq)
{

}

void PQClear(pq_t *pq)
{

}

void *PQErase(pq_t *pq, match_func_ptr m_ptr, void *param)
{

}
