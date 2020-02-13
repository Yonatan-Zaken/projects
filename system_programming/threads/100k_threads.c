#include <pthread.h> /* pthread_create */
#include <unistd.h>  /* sleep */
#include <stdio.h>   /* printf */


#define NUM_OF_THREADS (100000)
#define SUCCESS (1)

int arr[NUM_OF_THREADS];

static void CountSuccess()
{
    size_t counter = 0;
    size_t i = 0;
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        counter += arr[i];
    }
    
    printf("num of success : %lu\n", counter);
}

void *AssignThreadIndex(void *index)
{
    arr[(int)index] = SUCCESS;
    return NULL; 
}

int main()
{
    size_t i = 0;
    
    pthread_t threads[NUM_OF_THREADS];
    
    for (i = 0; i < NUM_OF_THREADS; ++i)
    {  
        while (0 != pthread_create (&(threads[i]), NULL, AssignThreadIndex, (void *)i));
        pthread_detach(threads[i]);
    }
 
    return 0;    
}

