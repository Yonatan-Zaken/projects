#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "work3.h"

int main(int argc, char *argv[],const char *envp[])
{
  
    const char **buffer = envp;
    char **result;
    result = CopyEnv(buffer);
    
    PrintEnv((const char**)result);
    CleanEnvCopy(result);
    
    return 0;
}
