#include <unistd.h> /* write */
#include <stdlib.h> /* sleep */
#include <fcntl.h>  /* O_ */
#include <sys/stat.h> /* mode_t */
#include <semaphore.h> /* sem_open */
#include <stdio.h> /* printf */

#define ITERATIONS 10
#define FAIL 1

int main()
{
    size_t j = 0;
    sem_t *ping = {0};
    sem_t *pong = {0};
 
    ping = sem_open("/ping", O_CREAT, 0644, 0);
    if (SEM_FAILED == ping)
    {
        return FAIL;
    }  
    
    pong = sem_open("/pong", O_CREAT, 0644, 0);
    if (SEM_FAILED == pong)
    {
        sem_close(ping);
        return FAIL;
    }
    
    for (j = 0; j < ITERATIONS; ++j)
    {
        sem_wait(pong);
        write(1, "pong\n", 5);
        sem_post(ping);      
    }
     
    sem_close(pong);
    sem_close(ping);
    
    return 0;
}
