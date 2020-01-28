#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>

typedef int (*compare_t)(const void*, const void*);
typedef int (*cmp_ptr_t)(const void *, const void *, void *param);

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

/* Gets a src array and dest array and the size of them, and sorts */
/* it in ascending order. */
/* Complexity in worst/average case O(nlog(n)) */
void MergeSort(int *src_arr, int* dest_arr, size_t size);

/* Gets an array the size of elements the number of elements     */
/* and a compare function and sorts the array in ascending order */
/* Complexity in worst case O(n^2) and average case O(nlog(n))   */
void QuickSort(void *base, size_t nmemb, size_t size, compare_t cmp);

/* Gets a sorted array, the size of elements the number of elements   */
/* and a compare function and searches the data specified by the user */
/* If not found returns NULL, otherwise returns the data found        */
/* Time complexity in worst case O(log(n))                            */
void *BinarySearch(void *arr, size_t element_size, size_t nmemb, cmp_ptr_t cmp,
                                                void *param, const void *data);

void *JumpSearch(void *arr, size_t element_size, size_t nmemb, cmp_ptr_t cmp,
                                                void *param, const void *data);
#endif
