#include <pthread.h> /* pthread_create */
#include <unistd.h>  /* sleep */
#include <stdio.h>   /* printf */
#include <stdlib.h>  /* atoi */

#define NUM_OF_THREADS 100
#define FAIL 1

typedef struct sum_divis_params
{
    size_t index;
    size_t num;
    size_t sum_of_divs;
} sod_t;

sod_t arr[NUM_OF_THREADS];

void *SumOfDividors(void *params)
{
    size_t i = 0;
    size_t thread_index = (size_t)params;
    size_t start = thread_index * (arr[thread_index].num / NUM_OF_THREADS) + 1;
    size_t end = (thread_index + 1) * (arr[thread_index].num / NUM_OF_THREADS);
    
    for (i = start; i <= end; ++i)
    {
        if (0 == (arr[(size_t)params].num % i))
        {
            arr[(size_t)params].sum_of_divs += i; 
        }
    }
   
    return NULL; 
}

int main(int argc, char *argv[])
{
    size_t i = 0;
    size_t sum = 0;
    int status = 0;
    
    pthread_t threads[NUM_OF_THREADS];
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        arr[i].num = atoi(argv[1]); 
        status = pthread_create(&(threads[i]), NULL, SumOfDividors, (void*)i);
        if (0 != status)
        {
            printf("Error pthread_create\n");
        }
    }
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (0 != pthread_join(threads[i], NULL))
        {
            printf("Error pthread_join\n");
            return FAIL;
        }
    }
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        sum += arr[i].sum_of_divs;
            
    }
    printf("sum of dividors : %lu\n", sum);  
    return 0;    
}
