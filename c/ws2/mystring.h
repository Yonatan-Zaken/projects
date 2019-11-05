/*********************************/
/*   			             	 */
/*				                 */
/* Header file for work sheet 2  */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by:		         */   
/*			                   	 */
/*			  	                 */
/*********************************/

#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

size_t StrLen(const char *str);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrnCpy(char *dest, const char *src, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *s, int c);
char *StrDup(const char* s);
char *StrCat(char *dest, const char *src);
char *StrnCat(char *dest, const char *src, size_t n);


#endif 
