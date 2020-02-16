#include <pthread.h> /* pthread_create */
#include <unistd.h>  /* sleep */
#include <stdio.h>   /* printf */
#include <stdatomic.h> /* atomic_int */

#define FAIL 1
#define NUM_OF_ELEMENTS 50
#define COUNTER 50

enum 
{
    WRITE,
    READ
};

int arr[NUM_OF_ELEMENTS] = {0};

atomic_int flag = WRITE;

void *Producer(void *param)
{
    size_t i = 0;
    size_t j = 0;
    
    for (i = 0; i < COUNTER; ++i)
    {
        while (__sync_lock_test_and_set(&flag, READ));
        for (j = 0; j < NUM_OF_ELEMENTS; ++j)
        {
            ++arr[j];            
        }
         __sync_lock_test_and_set(&flag, WRITE);      
    }     
}

void *Consumer(void *param)
{
    size_t i = 0;
    size_t j = 0;
    
    for (i = 0; i < COUNTER; ++i)
    {
        while (__sync_lock_test_and_set(&flag, READ));
        for (j = 0; j < NUM_OF_ELEMENTS; ++j)
        {
            printf("%d", arr[i]);            
        }
        printf("\n");
         __sync_lock_test_and_set(&flag, WRITE);      
    }   
}

int main()
{
    size_t i = 0;
    int status = 0;
    pthread_t producer;
    pthread_t consumer;
    
    status = pthread_create(&producer, NULL, Producer, NULL);
    if (0 != status)
    {
        printf("Error pthread_create\n");
    }
         
    status = pthread_create(&consumer, NULL, Consumer, NULL);
    if (0 != status)
    {
        printf("Error pthread_create\n");
    }
    
    if (0 != pthread_join(producer, NULL))
    {
        printf("Error pthread_join\n");
        return FAIL;
    }
    
    if (0 != pthread_join(consumer, NULL))
    {
        printf("Error pthread_join\n");
        return FAIL;
    }
    
    return 0;
}
