#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define PAGE_SIZE 4096

int main (int argc, char *argv[])
{
    key_t key = 0;
    int shmid = 0;
    char *data = NULL;
    
    if (-1 == (key = ftok("p1.c", 'L')))
    {
        perror("ftok");
        return 1;
    }
    
    if(-1 == (shmid = shmget(key, PAGE_SIZE, 0644 | 0)))
    {
        perror("shmid");
        return 1;
    }
    
    data = shmat(shmid, (void *)0, 0);
    if ((void *)(-1) == data)
    {
        perror("shmat");
        return 1;    
    }
    
    while (0 != memcmp(data, "exit", 4))
    {
        printf("%s\n", data);    
    }
    
    if (-1 == shmdt(data)) 
    {
        perror("shmdt");
        return 1;
    }
        
    return 0;
}
