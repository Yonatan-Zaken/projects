/*********************************/
/*   Sorting Algorithms          */
/*   Sort                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated: 6/1/2020      */
/*   Reviewed by: Itai           */
/*********************************/

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <alloca.h>

#include "sorts.h"

#define ON 1
#define OFF 0
#define BITS_IN_INT (sizeof(int) * 8)

#define FREE(ptr) free(ptr); ptr = NULL;

#define UNUSED(x) (void)(x)

void BubbleSort(int arr[], size_t n)
{
    size_t j = 0;
    size_t new_size = n - 1;
    size_t size = 0;
    int swap_temp = 0;
    int flag = ON;
    
    while (ON == flag)
    {
        flag = OFF;
        
        for (j = 0; j < new_size; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap_temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap_temp;
                
                size = j;
                flag = ON;
            }
        }
        new_size = size;
    }
}

void InsertionSort(int arr[], size_t n)
{
    int i = 0, j = 0;
    int max_temp = 0;
    
    for (i = 1; i < n; ++i)
    {   
        max_temp = arr[i];
        j = i - 1;
        while (0 <= j && arr[j] > max_temp)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = max_temp;       
    }
}

static void Swap(int *x, int *y)
{
    int temp = *y;
    *y = *x;
    *x = temp;
}

void SelectionSort(int arr[], size_t n)
{
    size_t i = 0, j = 0, jmin = 0;
    
    for (i = 0; i < (n - 1); ++i)
    {
        jmin = i;
        for (j = i + 1; j < n; ++j)
        {
            if(arr[j] < arr[jmin])
            {
                jmin = j;
            }    
        }
        if(jmin != i)
        {
            Swap(&arr[jmin], &arr[i]);
        }
    }
}

int CountingSort(const int *arr, size_t size, int min, int max, int *res)
{
    size_t *count = NULL;
    size_t range = (size_t)(max - min + 1);
    size_t i = 0;
    
    count = (size_t *)calloc(range, sizeof(size_t));
    if (NULL == count)
    {
        return 1;
    }
       
    for (i = 0; i < size; ++i)
    {
        count[arr[i] - min] += 1;
    }
    
    for (i = 1; i < range; ++i)
    {
        count[i] += count[i - 1];
    }       
    
    for (i = size - 1; i > 0; --i)
    {
        res[count[arr[i] - min] - 1] = arr[i];
        --count[arr[i] - min];
    }
    
    res[count[arr[i] - min] - 1] = arr[i];
    
    FREE(count);
    return 0;
}

static void RCountingSort(unsigned int *arr, size_t size, unsigned int mask, unsigned int shift, size_t *histogram, unsigned int *res)
{
    size_t hist_size = mask + 1;
    size_t i = 0;
    
    assert(NULL != arr);
    assert(NULL != histogram);
    assert(NULL != res);
    
    for (i = 0; i < hist_size; ++i)
    {
        histogram[i] = 0;
    }        
    
    for (i = 0; i < size; ++i)
    {
        ++histogram[(arr[i] >> shift) & mask];
    }
    
    for (i = 1; i < hist_size; ++i)
    {
        histogram[i] += histogram[i - 1];
    }
    
    for (i = size - 1; i > 0; --i)
    {
        res[histogram[(arr[i] >> shift) & mask] - 1] = arr[i];
        --histogram[(arr[i] >> shift) & mask];
    }
    
    res[histogram[(arr[i] >> shift) & mask] - 1] = arr[i];
}

static void SwapPtrs(unsigned int **dest, unsigned int **src)
{
    unsigned int *temp = NULL;
    temp = *dest;
    *dest = *src;
    *src = temp;     
}

int RadixSort(unsigned int *arr, size_t size, unsigned int num_of_bits)
{
    unsigned int mask = (1 << num_of_bits) - 1;
    unsigned int shift = 0;
    size_t i = 0;
    size_t *histogram = NULL;
    unsigned int *res = NULL;
    
    assert(NULL != arr);
    
    histogram = (size_t *)malloc((1 << num_of_bits) * sizeof(size_t));
    if (NULL == histogram)
    {
        return 1;        
    }
    
    res = (unsigned int *)malloc(size * sizeof(unsigned int));
    if (NULL == res)
    {
        FREE(histogram);
        return 1;
    }
    
    for (i = 0; i < (BITS_IN_INT / num_of_bits); ++i)
    {
        shift = i * num_of_bits;
        RCountingSort(arr, size, mask, shift, histogram, res);
        SwapPtrs(&arr, &res);
    }
    
    FREE(histogram);
    FREE(res);
    
    return 0;
}

static void Merge(int *dest_arr, size_t left, size_t middle, size_t right)
{
    size_t i = 0, j = 0, k = 0;
    size_t size1 = middle - left + 1;
    size_t size2 = right - middle;
    
    int *left_side = malloc(sizeof(int) * size1);
    int *right_side = malloc(sizeof(int) * size2);
    
    for (i = 0; i < size1; ++i)
    {
        left_side[i] = dest_arr[left + i];
    }
    
    for (j = 0; j < size2; ++j)
    {
        right_side[j] = dest_arr[middle + 1 + j];
    }
    
    i = 0; j = 0; k = left;
    
    while (i < size1 && j < size2)
    {
        if (left_side[i] <= right_side[j])
        {
            dest_arr[k] = left_side[i];
            ++i;
        }
        else
        {
            dest_arr[k] = right_side[j];
            ++j;
        }
        ++k;
    }
    
    while (i < size1)
    {
        dest_arr[k] = left_side[i];
        ++i;
        ++k;
    }
    
    while (j < size2)
    {
        dest_arr[k] = right_side[j];
        ++j;
        ++k;
    }
    
    free(left_side); left_side = NULL;
    free(right_side); right_side = NULL;
}

static void RecMergeSort(int *dest_arr, size_t left, size_t right)
{
    size_t middle = 0;
    
    if (left < right)
    {
        middle = left + (right - left) / 2;
        
        RecMergeSort(dest_arr, left, middle);
        RecMergeSort(dest_arr, middle + 1, right);
        
        Merge(dest_arr, left, middle, right);
    }
}

void MergeSort(int *src_arr, int* dest_arr, size_t size)
{
     size_t i = 0;
     
     assert(NULL != src_arr);
     
     for (i = 0; i < size; ++i)
     {
         dest_arr[i] = src_arr[i];
     }
     
     RecMergeSort(dest_arr, 0, size - 1);   
}

void SwapPtr(void *data1, void *data2, size_t element_size)
{
    void *temp = alloca(element_size);
    
    assert(NULL != data1);
    assert(NULL != data2);
    
    memcpy(temp, data1, element_size);
    memcpy(data1, data2, element_size);
    memcpy(data2, temp, element_size);
}

static void Partition(void *base, size_t size, size_t left, size_t right, compare_t cmp)
{
    size_t pivot_index = (left + right) / 2;
    size_t left_index = left;
    size_t right_index = right;
    char *runner = NULL;
    
    assert(NULL != base);
    
    runner = base;
    
    if (right_index <= left_index)
    {
        return;
    }
    
    while ((left_index <= pivot_index) && (right_index >= pivot_index))
    {
        while (0 > cmp(runner + size * left_index, runner + size * pivot_index) 
                              && left_index <= pivot_index)
        {
            ++left_index;
        }
        
        while (0 < cmp(runner + size * right_index, 
                       runner + size * pivot_index) && right_index >= pivot_index)
        {
            --right_index;
        }
        
        SwapPtr(runner + size * left_index, runner + size * right_index, size);
        ++left_index;
        --right_index;
        
        if ((left_index - 1) == pivot_index)
        {
            right_index += 1;
            pivot_index = right_index;
        }
        else if ((right_index + 1) == pivot_index)
        {
            left_index -= 1;
            pivot_index = left_index;
        }
    }
    
    if (0 < pivot_index)
    {
        Partition(base, size, left, pivot_index - 1, cmp);    
    }
    Partition(base, size, pivot_index + 1, right, cmp); 
}

void QuickSort(void *base, size_t nmemb, size_t size, compare_t cmp)
{    
    assert(NULL != base);
    
    Partition(base, size, 0, nmemb - 1, cmp);
}                                                                     

static void *RecBinarySearch(void *arr, size_t element_size, size_t left, size_t right,
                                          cmp_ptr_t cmp, void *param, const void *data)
{
    size_t mid = left + (right - left) / 2;
    int result = 0;
    char *runner = NULL;
     
    assert(NULL != arr);
    
    if (right >= left)
    {
        runner = (char *)arr + element_size * mid;
        result = cmp(runner, data, param);
        
        if (0 == result)
        {
            return runner;    
        }
        
        else if (0 < result)
        {
            return RecBinarySearch(arr, element_size, left, mid - 1, cmp,
                                                            param, data);
        }
        
        return RecBinarySearch(arr, element_size, mid + 1, right, cmp, param, data);
    }
    
    return NULL;
}

void *BinarySearch(void *arr, size_t element_size, size_t num_of_members,
                            cmp_ptr_t cmp, void *param, const void *data)
{
    size_t left = 0;
    size_t right = num_of_members - 1;
    
    assert(NULL != arr);
    
    return RecBinarySearch(arr, element_size, left, right, cmp, param, data);

}

void *JumpSearch(void *arr, size_t element_size, size_t num_of_members, cmp_ptr_t cmp,
                                                        void *param, const void *data)
{
    size_t jump_factor = sqrt(num_of_members);
    size_t i = 0;
    size_t remaining_members = 0;
    char *runner = arr;
    
    assert(NULL != arr);
    
    for (i = jump_factor; i < num_of_members; i += jump_factor)
    {            
        if (0 <= cmp(runner, data, param))
        {   
            runner -= element_size * jump_factor;
            return BinarySearch(runner, element_size, jump_factor + 1,
                                                    cmp, param, data);
        }
               
        runner += element_size * jump_factor;
    }
    
    remaining_members = num_of_members - (i - jump_factor);
    return BinarySearch(runner, element_size, remaining_members, cmp, param, data);
}

