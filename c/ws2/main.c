/*********************************/
/*   			             	 */
/*				                 */
/*   Test file for work sheet 2  */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by:		         */   
/*			                   	 */
/*			  	                 */
/*********************************/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <ctype.h>
#include "mystring.h"

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}


int main()
{
    
    char str1[] = "as";
    char str2[] = "abcde";
    char str3[] = "";
    char str4[] = "hello world";
    char str5[] = "HelLo WoRLD";
    char str6[] = "AA";
    char str7[] = "QQQQQ";
    
    
    printf("%s\n", strcpy(str1, str2));
    
	
/*	
	printf("StrLen : %ld\n", StrLen(str4));
	printf("strlen : %ld\n", strlen(str4));
	
	
	printf("StrCmp = %d\n", StrCmp(str3,str2));
	printf("StrCmp = %d\n", strcmp(str3,str2));
	
	
    printf("StrCpy : %s\n", StrCpy(str3, str4));
    printf("strcpy : %s\n", strcpy(str3, str4));
    
    
    printf("StrnCpy : %s\n", StrnCpy(str1, str2, 8));
    printf("StrnCpy : %s\n", StrnCpy(str1, str2, 2));
    printf("StrnCpy : %s\n", StrnCpy(str1, str3, 3));
    printf("strncpy : %s\n", strncpy(str1, str2, 8)); 
    printf("strncpy : %s\n", strncpy(str1, str2, 2));
    printf("strncpy : %s\n", strncpy(str1, str3, 3));
       
    printf("%s\n", StrDup(str5));
    printf("%s\n", StrCat(str1, str3));
    printf("%s\n", StrnCat(str1, str2, 15));
*/     
    return 0;
}
