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

#include "sorts.h"

#define ARR_SIZE 100000

static void Init(int arr[], size_t n)
{
    size_t i = 0;
    
    for (i = 0; i < n; ++i)
    {
        arr[i] = rand() % ARR_SIZE - 150;
    }
}

static void PrintArr(int arr[], size_t n)
{
    size_t i = 0;
    
    for (i = 0; i < n; ++i)
    {
        printf("%d\n", arr[i]);
    }
}

static void TestBubbleSort()
{
    clock_t begin = 0, end = 0;
    int *arr = NULL;
    
    arr = (int *)malloc(ARR_SIZE * sizeof(int));
    Init(arr, ARR_SIZE);
    begin = clock();
    BubbleSort(arr, ARR_SIZE);
    end = clock();
    /*PrintArr(arr, ARR_SIZE);*/
    printf("Bubble Sort: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    free(arr); arr = NULL;    
}

static void TestInsertionSort()
{
    clock_t begin = 0, end = 0;
    int *arr = NULL;
    
    arr = (int *)malloc(ARR_SIZE * sizeof(int));
    Init(arr, ARR_SIZE);
    begin = clock();
    InsertionSort(arr, ARR_SIZE);
    end = clock();
    /*PrintArr(arr, ARR_SIZE);*/
    printf("Insertion Sort: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    free(arr); arr = NULL;    
}

static void TestSelectionSort()
{
    clock_t begin = 0, end = 0;
    int *arr = NULL;
    
    arr = (int *)malloc(ARR_SIZE * sizeof(int));
    Init(arr, ARR_SIZE);
    begin = clock();
    SelectionSort(arr, ARR_SIZE);
    end = clock();
    /*PrintArr(arr, ARR_SIZE);*/
    printf("Selection Sort: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    free(arr); arr = NULL;    
}

static void TestCountingSort()
{
    clock_t begin = 0, end = 0;
    int *arr = NULL;
    int *res = NULL;
    
    arr = (int *)malloc(ARR_SIZE * sizeof(int));
    res = (int *)malloc(ARR_SIZE * sizeof(int));
    Init(arr, ARR_SIZE);
   
    begin = clock();
    CountingSort(arr, ARR_SIZE, -150, ARR_SIZE, res);
    end = clock();
    /*PrintArr(arr, ARR_SIZE);*/
    printf("Counting Sort: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    free(arr); arr = NULL;
    free(res); res = NULL;    
}

int main()
{
    TestBubbleSort();
    TestInsertionSort();
    TestSelectionSort();
    TestCountingSort();
    
    return 0;  
}

