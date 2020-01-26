#ifndef __HEAPIFY_H__
#define __HEAPIFY_H__

#include <stddef.h> /* size_t */

/* Rearranges an array to maintain that the root element is greater or less than or equal to the keys of its children. Time Complexity O(log(n))*/
void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size
                                     compare_func_ptr cmp, void *param);

void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size
                                       compare_func_ptr cmp, void *param);

#endif
