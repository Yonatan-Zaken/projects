#include <stdio.h>      /* printf   */
#include <stddef.h>     /* offsetof */
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
    size_t i = 0;
    size_t msg_buf_size = 0;
    key_t key = 0;
    struct msg_buf buffer = {0};
    
    buffer.mtype = 1;
    memcpy(buffer.text, "P1 message queue", 20);
    
    msg_buf_size = sizeof(struct msg_buf) - offsetof(struct msg_buf, text);
    
    if (-1 == (key = ftok("mq_read.c", 'Z'))) 
    {
        perror("ftok");
        return 1;
    }
    
    if (-1 == (msqid = msgget(key, 0644 | IPC_CREAT))) 
    {
        perror("msgget");
        return 1;
    }    
    /*
    if (-1 == msgsnd(msqid, &buffer, msg_buf_size, 0)) 
    {
        perror("msgsnd");
        return 1;    
    }
    */
    for (i = 0; i < 10; ++i)
    {
        fgets(buffer.text, sizeof(buffer.text), stdin);
        if (-1 == msgsnd(msqid, &buffer, msg_buf_size, 0)) 
        {
            perror("msgsnd");
            return 1;
        }
    }

    return 0;
}
