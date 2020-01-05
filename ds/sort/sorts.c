/*********************************/
/*   Sorting Algorithms          */
/*   Sort                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated: 5/1/2020      */
/*   Reviewed by: Daniel         */
/*********************************/

#include <stdlib.h>

#include "sorts.h"

#define ON 1
#define OFF 0

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
    int *count = NULL;
    size_t range = (size_t)(max - min + 1);
    size_t i = 0;
    
    count = (int *)calloc(range, sizeof(int));
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
    
    free(count); count = NULL;
    return 0;
}
