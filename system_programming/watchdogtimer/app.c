#include <stdio.h>

#include "wd.h"

int main()
{
    status_t status;
    
    wd_t *wd = WDStart("app.c", &status);
          
    WDStop(wd);
    
    return 0;
}

