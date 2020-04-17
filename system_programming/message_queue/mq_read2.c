#include <stdio.h>      /* printf   */
#include <stddef.h>     /* offsetof */
#include <stdlib.h>     
#include <errno.h>      /* perror   */
#include <string.h>     /* strlen   */
#include <sys/types.h>  /* key_t    */
#include <sys/ipc.h>    /* ftok     */
#include <sys/msg.h>    /* msgget   */

struct msg_buf
{
    long mtype;
    char text[50];
};

int main (int argc, char *argv[])
{
    int msqid = 0;
    key_t key = 0;
    struct msg_buf msgptr = {0};
    
    if (-1 == (key = ftok("mq_read.c", 'Z'))) 
    {
        perror("ftok");
        return 1;
    }
    
    if (-1 == (msqid = msgget(key, 0644))) 
    {
        perror("msgget");
        return 1;
    }    
    
    if (-1 == msgrcv(msqid, &msgptr, sizeof(struct msg_buf) - offsetof(struct msg_buf, text), 0, 0)) 
    {
        perror("msgrcv");
        return 1;    
    }
    
    printf("%s\n", msgptr.text);

    return 0;
}
