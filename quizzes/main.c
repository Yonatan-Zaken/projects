#include <string.h>
#include <stdio.h>
#include "IsRotate.h"

void TestFunc(int condition, const char *message)
{
    
    if (1 == condition)
    {   
        printf("\033[0;32m");
        printf("%s %s\n", "SUCCESS", message);
    }
    
    else
    {
        printf("\033[1;31m");
        printf("%s %s\n", "FAIL", message);
    }
    
    printf("\033[0m"); 
}

int main()
{	
	
	TestFunc(IsRotate("121234", "123412") == 1, "simple true");
	
	TestFunc(IsRotate("1112223", "1222311") == 1, "simple true");

	TestFunc(IsRotate("123", "1") == 0, "different sizes");

	TestFunc(IsRotate("123124125", "251231241") == 1, "true");


	return 0;
}
