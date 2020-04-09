#include <stdio.h>

#include "ext2.h"

int main(int argc, char *argv[])
{
    
    PrintSuperBlock(argv[1]);   
    PrintGroupDescriptors(argv[1]);
    PrintFileContent(argv[1], argv[2]);
    return 0;
}

