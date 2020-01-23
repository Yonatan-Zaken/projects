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

/* Gets an array and the array size and sorts it in ascending order. */
/* min and max are the limits for the range of possible value        */
/* Complexity: worst case O(n + k), where k is the range             */ 
int CountingSort(const int arr[], size_t size, int min, int max, int res[]);

/* Gets an array and the array size and sorts it in ascending order. */
/* num_of_bits defines the range of each bucket                      */
/* Complexity: worst case O(n*d), where d is the number of digits    */ 
int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits);

void MergeSort(int *src_arr, int* dest_arr, size_t size);

#endif
