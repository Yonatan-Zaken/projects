#include <stdio.h>
#include "funWS2.h"

int main()
{
    char str1[] = "fgh";
    char str2[] = "abcde";

    printf("%s\n\n",StrnCpy(str1, str2, 7));
    
	
    return 0;
}
