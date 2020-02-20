/*********************************/
/*   			             	 */
/*   System Programming          */
/*   Watch Dog Timer             */
/*   Author: Yonatan Zaken       */
/*   Last Updated 20/2/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/
#include <sys/types.h> /* pid_t    */
#include <unistd.h>    /* getpid() */
#include <fcntl.h>     /* For O_* constants */
#include <sys/stat.h>  /* For mode constants */
#include <semaphore.h> /* sem_open () */
#include <signal.h> /* sigaction () */

#include "scheduler.h"
#include "wd.h"

size_t is_wd_alive = 0;
pid_t updated_id = {0};

sem_t sem_is_wd_up = {0};
sem_t sem_top_flag = {0};
sem_t sem_wd_ready = {0};
sem_t sem_app_ready = {0};

void HandlerStopSignIMP(int signal)
{

}

void HandlerImAliveIMP(int signal)
{

}

scheduler_t *WDInitIMP()
{
    
}

void *SchedulerRunIMP(void *pack)
{

}

wd_t *WDStart(const char *filename, enum *status)
{
    
}

void WDStop(wd_t *wd)
{


}
