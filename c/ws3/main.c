#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "work3.h"

int main(int argc, char *argv[], char **envp)
{
    
    const char **array = (const char**) envp;
    
    CopyEnv(array);
   /* PrintEnv(array);*/
    
    return 0;
}
