#include <stdio.h>  /* printf () */
#include <unistd.h> /* time_t */
#include <time.h>   /* sleep () */

#include "wd.h"

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{  
    status_t status = 0;
    time_t sleep_delay = 100;
    wd_t *wd = WDStart(
    "/home/yonatan10/yonatan-zaken/system_programming/watchdogtimer/outdebug/app", &status);

    UNUSED(argc);
    UNUSED(argv);
        
    while (sleep_delay)
    {
        sleep_delay = sleep(sleep_delay);
    }
    
    WDStop(wd);
    
    return 0;
}

