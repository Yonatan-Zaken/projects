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

int main()
{
    
    char str1[] = "fgh";
    char str2[] = "abcde";
    char str3[] = "";
    char str4[] = "hello world";
    char str5[] = "HelLo WoRLD";
	
	/*check strlen*/
	printf("StrLen : %ld\n", StrLen(str4));
	printf("strlen : %ld\n", strlen(str4));
	
	/*check strcmp */
	printf("StrCmp = %d\n", StrCmp(str3,str2));
	printf("StrCmp = %d\n", strcmp(str3,str2));
	
	/* check strcpy */
/*    printf("StrCpy : %s\n", StrCpy(str3, str4));*/
/*    printf("strcpy : %s\n", strcpy(str3, str4));*/
    
    /* check strncpy */
/*    printf("StrnCpy : %s\n", StrnCpy(str1, str2, 8));*/
/*    printf("StrnCpy : %s\n", StrnCpy(str1, str2, 2));*/
/*    printf("StrnCpy : %s\n", StrnCpy(str1, str3, 3));*/
/*    printf("strncpy : %s\n", strncpy(str1, str2, 8)); */
/*    printf("strncpy : %s\n", strncpy(str1, str2, 2));*/
/*    printf("strncpy : %s\n", strncpy(str1, str3, 3));*/
    
    /* check strcasecmp */
    
    printf("StrCaseCmp = %d\n", StrCaseCmp(str4,str5));
    printf("strcasecmp = %d\n", strcasecmp(str4,str5));
    
    /* check strchr */
    
    printf("StrChr : %s\n", StrChr(str5, 'l'));
/*    printf("strchr : %s\n", strchr(str5, 'l'));*/
/*    */
    
    
       
    return 0;
}
