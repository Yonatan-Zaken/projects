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

#include "sorts.h"

#define ON 1
#define OFF 0
#define BITS_IN_INT (sizeof(int) * 8)

#define FREE(ptr) free(ptr); ptr = NULL;

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
        free(histogram); histogram = NULL;
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






