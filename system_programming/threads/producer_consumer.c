#include <pthread.h> /* pthread_create */
#include <unistd.h>  /* sleep */
#include <stdio.h>   /* printf */
#include <stdatomic.h>

#define FAIL 1;
#define NUM_OF_ELEMENTS 5
#define COUNTER 100 
#define NUM_OF_THREADS 2

enum 
{
    WRITE,
    READ
};

int arr[NUM_OF_ELEMENTS] = {0};

atomic_int flag = READ;

/*atomic_flag_test_and_set(volatile atomic_flag* obj);*/

void *Producer(void *param)
{
    size_t i = 0;
    size_t j = 0;
    
    while ((COUNTER > j))
    {
        while (READ == flag);
        for (i = 0; i < NUM_OF_ELEMENTS; ++i)
        {
            arr[i] += 1;            
        }
        ++j;
        flag = READ;
    }
        
}

void *Consumer(void *param)
{
    size_t i = 0;
    size_t j = 0;
    
    while ((COUNTER > j))
    {
        while (WRITE == flag);
        for (i = 0; i < NUM_OF_ELEMENTS; ++i)
        {
            printf("%d\n", arr[i]);        
        }
        ++j;
        flag = WRITE;    
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
