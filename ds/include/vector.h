/*********************************/
/*   			             	 */
/*   Header file DS 3            */
/*   Yonatan Zaken		         */
/*   Last Updated 1/12/19        */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct Vector vector_t;

/* This function creates the vector */
vector_t* VectorCreate(size_t element_size, size_t capacity);

/* This function destroy the vector */
/* Warning: the function doesn't get NULL pointer */
void VectorDestroy(vector_t *myvector);

/* This function push new item at the end of the vector */
/* 0 - success , 1- failure */
/* Warning: Could resize the capacity in an unpredictable manner */
/* Warning: the function doesn't get NULL pointer */
int VectorPushBack(vector_t *myvector, const void* data);

/* This function pops the last item in the vector */
/* Warning: the function doesn't get NULL pointer */
void VectorPopBack(vector_t *myvector);

/* This function resizing the vector size as needed with extra space */
/* 0 - success , 1- failure */
/* Warning: the function doesn't get NULL pointer */
int VectorReserve(vector_t *myvector, size_t new_capacity);

/* This function return the total size of the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorCapacity(const vector_t *myvector);

/* This function return the current number of elements in the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorSize(const vector_t *myvector);

/* This function return specific item address to the user */
/* Warning: the address is valid until using PopBack/PushBack over the limit */
/* Warning: the function doesn't get NULL pointer */
void* VectorGetItemAddress(const vector_t *myvector, size_t position);

#endif

