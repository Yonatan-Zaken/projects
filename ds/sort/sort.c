/*********************************/
/*   Sorting Algorithms          */
/*   Sort                 */
/*   Author: Yonatan Zaken       */
/*   Last Updated        */
/*   Reviewed by:          */
/*********************************/

#include "sort.h"

#define ON 1
#define OFF 0

void BubbleSort(int arr[], size_t n)
{
    size_t i = 0, j = 0;
    size_t new_size = n - 1;
    size_t size = 0;
    int temp = 0;
    int flag = 0;
    
    for (i = 0; i < (n - 1); ++i)
    {
        flag = OFF;
        
        for (j = 0; j < new_size; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
                size = j;
                flag = ON;
            }
        }
        
        new_size = size;
        if (OFF == flag)
        {
            break;
        }
    }
}

void InsertionSort(int arr[], size_t n)
{
    int i = 0, j = 0;
    int temp = 0;
    
    for (i = 1; i < n; ++i)
    {   
        temp = arr[i];
        j = i - 1;
        while (0 <= j && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        
        arr[j + 1] = temp;       
    }
}

void Swap(int *x, int *y)
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






