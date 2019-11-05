#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
#include <string.h>
#include "mystring.h"


int main()
{
    char str1[] = "abcd";
    char str2[] = "";
    char str3[] = "";
    char str4[] = "halo halo";
    char str5[] = "whaaaaaaaaaaaaat";
    char str6[] = "bbbb";
    char str7[] = "aahhh";
    char str8[] = "aCdd";
    char str9[] = "aCdC";
    char str10[] = "arrggg";
    
    /*strlen*/
    printf("strlen : %ld\n", mystrLen(str1));
    
    /*strcmp*/
    printf("strcmp : %d\n", MyStrCmp(str2, str3));
    
    /*strcpy*/
    printf("strcpy : %s\n", MyStrCpy(str4, str5));
    
    /*strncpy*/
    printf("strncpy : %s\n", mystrncpy(str6,str7,2));
    
    /*strcasecmp*/
    printf("strcasecmp : %d\n", mystrcasecmp(str8, str9));
    
    /*strchr*/
    printf("strchr : %s\n", mystrchr(str10,'r'));
    
    return 0;

}
