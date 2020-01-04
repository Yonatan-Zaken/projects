/*********************************/
/*   Sort Algorithms Test File   */
/*   Sort                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated        */
/*   Reviewed By: */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

#define ARR_SIZE 5000

void Init(int arr[], size_t n)
{
    size_t i = 0;
    
    for (i = 0; i < n; ++i)
    {
        arr[i] = rand() % 1000;
    }
}

void PrintArr(int arr[], size_t n)
{
    size_t i = 0;
    
    for (i = 0; i < n; ++i)
    {
        printf("%d\n", arr[i]);
    }
}

int main()
{
    clock_t begin = 0, end = 0;
    int arr[ARR_SIZE] = {0};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    Init(arr, size);

    begin = clock();
    /*BubbleSort(arr, size);*/
    /*InsertionSort(arr, size);*/
    SelectionSort(arr, size);
    end = clock();
    PrintArr(arr, size);   
    printf("time spent: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return 0;
}

