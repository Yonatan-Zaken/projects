#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>

/* Gets an array and the array size and sorts it   */
/* in ascending order. Complexity: best case O(n)  */
/* worst case O(n^2)                               */ 
void BubbleSort(int arr[], size_t n);

/* Gets an array and the array size and sorts it   */
/* in ascending order. Complexity: best case O(n)  */
/* worst case O(n^2)                               */ 
void InsertionSort(int arr[], size_t n);

/* Gets an array and the array size and sorts it    */
/* in ascending order. Complexity: best case O(n^2) */
/* worst case O(n^2)                                */ 
void SelectionSort(int arr[], size_t n);

int CountingSort(const int arr[], size_t size, int min, int max, int res[]);

int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits);

#endif
