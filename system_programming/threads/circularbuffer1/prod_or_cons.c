#include <stdio.h>   /* printf */
#include <assert.h>  /* assert */
#include <pthread.h> /* pthread_create */
#include <semaphore.h> /* sem_init */

#include "circularbuffer.h"

#define FAIL 1
#define PRODUCERS 8
#define CONSUMERS 5
#define CAPACITY 5

pthread_mutex_t lock = {0};
sem_t prod_jobs = {0};
sem_t cons_jobs = {0};
int insert_value = 0;

void *Producer(void *data)
{
    assert(NULL != data);
    
    sem_wait(&prod_jobs);
    pthread_mutex_lock(&lock);
    CBufferWrite((cbuffer_t*)data, insert_value);
    printf("Write %d\n", insert_value);
    ++insert_value;     
    sem_post(&cons_jobs);
    pthread_mutex_unlock(&lock); 
    
    return NULL;   
}

void *Consumer(void *data)
{
    assert(NULL != data);
    
    sem_wait(&cons_jobs);
    pthread_mutex_lock(&lock);
    printf("%d\n", CBufferRead((cbuffer_t *)data));
    sem_post(&prod_jobs);
    pthread_mutex_unlock(&lock);
    
    return NULL;
}    

int main()
{
    size_t i = 0;
    int status = 0;
    cbuffer_t *cbuffer = NULL;
    
    pthread_t producers[PRODUCERS];
    pthread_t consumers[CONSUMERS];
    
    pthread_mutex_init(&lock, NULL);
    sem_init (&prod_jobs, 0, CAPACITY);
    sem_init (&cons_jobs, 0, 0);

    cbuffer = CBufferCreate(CAPACITY);
    if (NULL == cbuffer)
    {
        return FAIL;
    }
    
    for (i = 0; i < PRODUCERS; ++i)
    {
        status = pthread_create(&(producers[i]), NULL, Producer, cbuffer);
        if (0 != status)
        {
            printf("Error pthread_create\n");
            return FAIL;
        }
    }
    
    for (i = 0; i < CONSUMERS; ++i)
    {
        status = pthread_create(&(consumers[i]), NULL, Consumer, cbuffer);
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
    
    CBufferDestroy(cbuffer);
    pthread_mutex_destroy(&lock);
    sem_destroy(&prod_jobs);
    sem_destroy(&cons_jobs);
    
    return 0;
}
