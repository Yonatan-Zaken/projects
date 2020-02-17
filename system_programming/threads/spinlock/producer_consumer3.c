#include <stdio.h>   /* printf */
#include <time.h>    /* time */
#include <assert.h>  /* assert */
#include <pthread.h> /* pthread_create */
#include <stdatomic.h> /* atomic_int */

#include "dllist.h"

#define FAIL 1
#define PRODUCERS 5
#define CONSUMERS 5

pthread_mutex_t lock = {0};
int insert_value = 1;

void *Producer(void *data)
{
    assert(NULL != data);
    
    pthread_mutex_lock(&lock);
    DLLPushBack((dll_t *)data, &insert_value); 
    printf("Push size: %lu\n", DLLSize((dll_t*)data));   
    pthread_mutex_unlock(&lock); 
    
    return NULL;   
}

void *Consumer(void *data)
{
 
    time_t end = 0;
    time_t start = time(NULL);
    time_t seconds = 7; 

    assert(NULL != data);

    end = start + seconds;   
       
    while (start < end)
    {
        start = time(NULL);
        pthread_mutex_lock(&lock); 
        if (!DLLIsEmpty((dll_t*)data))
        {    
            printf("Pop Output: %d\n", *(int*)DLLPopFront((dll_t *)data)); 
        }  
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}    

int main()
{
    size_t i = 0;
    int status = 0;
    dll_t *dll = NULL;
    
    pthread_t producers[PRODUCERS];
    pthread_t consumers[CONSUMERS];
    
    pthread_mutex_init(&lock, NULL);
    
    dll = DLLCreate();
    if (NULL == dll)
    {
        return FAIL;
    }
    
    for (i = 0; i < PRODUCERS; ++i)
    {
        status = pthread_create(&(producers[i]), NULL, Producer, dll);
        if (0 != status)
        {
            printf("Error pthread_create\n");
            return FAIL;
        }
    }
    
    for (i = 0; i < CONSUMERS; ++i)
    {
        status = pthread_create(&(consumers[i]), NULL, Consumer, dll);
        if (0 != status)
        {
            printf("Error pthread_create\n");
            return FAIL;
        }
    }
    
    for (i = 0; i < PRODUCERS; ++i)
    {
        pthread_join(producers[i], NULL);
    }
    
    for (i = 0; i < CONSUMERS; ++i)
    {
        pthread_join(consumers[i], NULL);
    }
    
    DLLDestroy(dll);
    pthread_mutex_destroy(&lock);
    
    return 0;
}
