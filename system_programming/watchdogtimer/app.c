#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <time.h>

#include "wd.h"

int main()
{
    status_t status;
    time_t sleep_delay = 100;
    
    wd_t *wd = WDStart("app.c", &status);
 
    while (sleep_delay)
    {
        sleep_delay = sleep(sleep_delay);
    }
    
    WDStop(wd);
    
    printf("App is alive!\n");
    
    sleep_delay = 10;
    
    while (sleep_delay)
    {
        sleep_delay = sleep(sleep_delay);
    }
    
    return 0;
}

