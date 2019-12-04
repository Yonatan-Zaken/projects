/*********************************/
/*   			             	 */
/*				                 */
/* Implement file work sheet 2   */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by:		         */   
/*			                   	 */
/*			  	                 */
/*********************************/

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "mystring.h"


/*****************************************/
/*			                             */
/*     strlen function  for WS 2         */
/*					                     */
/*****************************************/

/* This function gets a string and returns its length*/

size_t StrLen(const char *str)
{
    const char *runner = str;	
    
    /* Check if str points to \0 in debug mode */
    assert(NULL != str); 
    
    while ('\0' != *runner)	
    {
        ++runner;
    }            
    
    return (runner - str);

}

/*****************************************/
/*			                             */
/*     strcmp function  for WS 2         */
/*					                     */
/*****************************************/

/* This function gets two strings,
   compares them and returns a value accordingly */

int StrCmp(const char *s1, const char *s2)
{
    const char *runner1 = s1;
    const char *runner2 = s2;    
        
    /* Check if s1/s2 point to '\0' in debug mode */    
    assert(NULL != s1);
    assert(NULL != s2);  
            
    while (*runner1 == *runner2 && '\0' != *runner1)
    {
        ++runner1;
        ++runner2;
    }
    
    return (*runner1 - *runner2);
}

/*****************************************/
/*			                             */
/*     strcpy function  for WS 2         */
/*					                     */
/*****************************************/

/* This function gets 2 strings and copies the
   source string to the destination string    */

char *StrCpy(char *dest, const char *src)
{
    char *runner1 = dest;
    /*char temp[StrLen(src) + 1];*/
    const char *runner2 = src;
    
    /* Check if src/dest point to '\0' in debug mode */
    assert(NULL != src && NULL != dest);
    
    while( '\0' != *runner2)
    {
        *runner1 = *runner2;
        ++runner1;     
        ++runner2;    
    }    
    
    *runner1 = '\0';        
    
    return dest;
}


/*****************************************/
/*			                             */
/*     strncpy function  for WS 2        */
/*					                     */
/*****************************************/

/* This function gets 2 strings and copies n elements
   from source to the destination string            */

char *StrnCpy(char *dest, const char *src, size_t n)
{
    char *runner1 = dest;
    const char *runner2 = src;
    unsigned int i = 0;
    
    /* Check if src/dest point to '\0' in debug mode */
    assert(NULL != src && NULL != dest);
    
    if ( 0 == n)
    {
        return dest;
    }
    
    while (i < n && '\0' != *runner2)
    {
        *runner1 = *runner2;
        ++runner1;
        ++runner2;
        ++i;
    }    
    
    *runner1 = '\0';        
    
    return dest;
}

/*****************************************/
/*			                             */
/*     strcasecmp function for WS 2      */
/*					                     */
/*****************************************/

/* This function gets 2 strings and compares them
   regardless of upper/lower case and returns a 
    value accordingly                          */

int StrCaseCmp(const char *s1, const char *s2)
{
    const char *runner1 = s1;
    const char *runner2 = s2;
   
    
    /* Check if src/dest point to '\0' in debug mode */
    assert(NULL != s1 && NULL != s2);    
        
    while (tolower(*runner1) == tolower(*runner2) && 
                                   '\0' != *runner1)
    {
        ++runner1;
        ++runner2;
    }
    
    
    return (tolower(*runner1)-tolower(*runner2));
}

/*****************************************/
/*			                             */
/*     strchr function for WS 2          */
/*					                     */
/*****************************************/

/* This function gets a string and a character and
   returns a string starting from the character. 
   If the character doesnt exist returns NULL    */

char *StrChr(const char *s, int c)
{
    const char *runner = s; 
    /*char *temp = NULL;*/
    
    assert(NULL != s);
   
    while (c != *runner && '\0' != *runner)
    {
        ++runner;            
    }
    
    if('\0' == *runner)
    {
        return NULL;        
    }

    return ((char*)runner);
}

/*****************************************/
/*			                             */
/*     strdup function for WS 2          */
/*					                     */
/*****************************************/

/* !!Don't forget to free allocated memory!! */
char *StrDup(const char* s)
{
    int str_size = StrLen(s) + 1; 
    
    char *temp = (char*)malloc(sizeof(char) * str_size);
   
       
    
    const char *runner = s;
    assert(NULL != s);
    
 
    
    assert(NULL != temp);
    
    if(NULL == temp) 
    {
        return NULL;
    }
    
    strcpy(temp, runner);
        
    return temp;
    
}

/*****************************************/
/*			                             */
/*     strcat function for WS 2          */
/*					                     */
/*****************************************/

/* !!Dest string must have enough space for the result!! */
char *StrCat(char *dest, const char *src)
{
   char *runner1 = dest;
   const char *runner2 = src;
   
   while ('\0' != *runner1)
   {
        ++runner1;     
   } 
        
   while('\0' != *runner2)
   {
        *runner1 = *runner2;
        ++runner1;
        ++runner2;     
   }
   
   *runner1 = '\0';
   
   return dest;
   
}

/*****************************************/
/*			                             */
/*     strncat function for WS 2         */
/*					                     */
/*****************************************/

/* !!Dest string must have enough space for the result!! */
char *StrnCat(char *dest, const char *src, size_t n)
{
   char *runner1 = dest;
   const char *runner2 = src;
   unsigned int i = 0;
   
   while ('\0' != *runner1)
   {
        ++runner1;     
   } 
        
   while('\0' != *runner2 && i < n)
   {
        *runner1 = *runner2;
        ++runner1;
        ++runner2;
        ++i;     
   }
   
   *runner1 = '\0';
   
   return dest;
}









