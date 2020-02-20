#include <stdio.h>   /* printf */
#include <assert.h>  /* assert */
#include <pthread.h> /* pthread_create */
#include <semaphore.h> /* sem_init */

#define FAIL 1
#define PRODUCERS 1
#define CONSUMERS 8

pthread_mutex_t lock = {0};
sem_t prod_jobs = {0};
pthread_cond_t producer_cond = {0};

size_t signal_flag = 0;
int product_job = 0;

void *Producer(void *data)
{ 
    size_t i = 0;
    
    while (1)
    {
        for (i = 0; i < CONSUMERS; ++i)
        {
            sem_wait(&prod_jobs);
        }
        pthread_mutex_lock(&lock);
        printf("job done!\n");
        ++product_job;
        pthread_cond_broadcast(&producer_cond);
        pthread_mutex_unlock(&lock);     
    }  
    
    return data;    
}

void *Consumer(void *data)
{
    int flag = 0;
    
    while (1)
    {
        flag = product_job;
        pthread_mutex_lock(&lock);
        sem_post(&prod_jobs);        
        while (flag == product_job)
        {
            pthread_cond_wait(&producer_cond, &lock);     
        }
        printf("%d\n", product_job);
        pthread_mutex_unlock(&lock);
    }
    
    return data;
}    

int main()  
{
    size_t i = 0;
    int status = 0;
    
    pthread_t producers[PRODUCERS];
    pthread_t consumers[CONSUMERS];
    
    pthread_mutex_init(&lock, NULL);
    sem_init (&prod_jobs, 0, 0);
    pthread_cond_init(&producer_cond, NULL);
       
    for (i = 0; i < PRODUCERS; ++i)
    {
        status = pthread_create(&(producers[i]), NULL, Producer, NULL);
        if (0 != status)
        {
            printf("Error pthread_create\n");
            return FAIL;
        }
    }
    
    for (i = 0; i < CONSUMERS; ++i)
    {
        status = pthread_create(&(consumers[i]), NULL, Consumer, NULL);
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
    
    pthread_mutex_destroy(&lock);
    sem_destroy(&prod_jobs);
    pthread_cond_destroy(&producer_cond);
    
    return 0;
}
