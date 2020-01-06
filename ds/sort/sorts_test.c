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
#include <string.h>

#include "sorts.h"

#define ARR_SIZE 100000
#define FREE(ptr) free(ptr); ptr = NULL;

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

static void Init(int arr[], size_t n)
{
    size_t i = 0;
    
    for (i = 0; i < n; ++i)
    {
        arr[i] = rand() % (ARR_SIZE*8);
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
    
    FREE(arr);    
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
    
    FREE(arr);    
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
    
    FREE(arr);    
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
    CountingSort(arr, ARR_SIZE, -ARR_SIZE, ARR_SIZE, res);
    end = clock();
    /*PrintArr(arr, ARR_SIZE);*/
    printf("Counting Sort: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    FREE(arr);
    FREE(res);    
}
static int cmpfunc(const void *data1, const void *data2)
{
    return (*(int*)data1 - *(int*)data2);
}

static void TestRadixSort()
{
    clock_t begin = 0, end = 0;
    unsigned int *arr = NULL;
    unsigned int *arr2 = NULL;
    
    arr = (unsigned int *)malloc(ARR_SIZE * sizeof(int));
    arr2 = (unsigned int *)malloc(ARR_SIZE * sizeof(int));
    Init((int *)arr, ARR_SIZE);
    
    arr2 = memcpy(arr2, arr, ARR_SIZE * sizeof(int));
    
    begin = clock();
    qsort(arr2, ARR_SIZE, sizeof(int), &cmpfunc);
    end = clock();
    /*PrintArr((int *)arr2, ARR_SIZE);*/
    printf("Q Sort: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    begin = clock();
    RadixSort(arr, ARR_SIZE, 4);
    end = clock();
    /*PrintArr((int *)arr, ARR_SIZE);*/
    printf("Radix Sort: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    RUN_TEST(0 == memcmp(arr, arr2, ARR_SIZE * sizeof(int)), "test");
    
    FREE(arr);
    FREE(arr2);
}

int main()
{
    /*TestBubbleSort();
    TestInsertionSort();
    TestSelectionSort();
    TestCountingSort();*/
    TestRadixSort();
    
    return 0;  
}

