#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ws4head.h"

int main()
{
    
    int (*lut_ptr[256])(char);
    LutInit(lut_ptr, 256);
    
    return 0;
}
