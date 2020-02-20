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
    size_t i = 0;
    sem_t *ping = {0};
    sem_t *pong = {0};
 
    ping = sem_open("/ping", O_CREAT, 0644, 0);
    if (SEM_FAILED == ping)
    {
        printf("Fail sem_open");
        return FAIL;
    } 
    
    pong = sem_open("/pong", O_CREAT, 0644, 0);   
    if (SEM_FAILED == pong)
    {
        printf("Fail sem_open");
        sem_close(ping);
        sem_unlink("/ping");
        return FAIL;
    } 
    
    for (i = 0; i < ITERATIONS; ++i)
    {
        write(1, "ping\n", 5);
        sem_post(pong);
        sleep(1);
        sem_wait(ping);    
    }           
    
    sem_close(pong);
    sem_close(ping);
    
    sem_unlink("/ping");
    sem_unlink("/pong");
    
    return 0;
}
