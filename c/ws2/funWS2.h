#include <stdio.h>
#include <assert.h>
#include <ctype.h>

/*****************************************/
/*			                             */
/*     strlen function  for WS 2         */
/*					                     */
/*****************************************/

size_t StrLen(const char *str)
{
	
	assert(NULL != str);
	
    const char *runner = str;
    
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

int StrCmp(const char *s1, const char *s2)
{
    const char *runner1 = s1;
    const char *runner2 = s2;
    int return_val = 0;    
        
    while (*runner1 == *runner2 && '\0' != *runner1)
    {
        ++runner1;
        ++runner2;
    }
    
    if(*runner1 > *runner2)
    {
        return_val = 1;    
    }
    
    else if(*runner1 < *runner2)
    {
        return_val = -1;
    } 
    
    return (return_val);
}

/*****************************************/
/*			                             */
/*     strcpy function  for WS 2         */
/*					                     */
/*****************************************/

char *StrCpy(char *dest, const char *src)
{
    char temp[StrLen(src) + 1];
    const char *runner = src;
    int i = 0;
    
    while( '\0' != *runner)
    {
        temp[i] = *runner;
        ++i;     
        ++runner;    
    }    
    
    temp[i] = '\0';    
    dest = temp;    
    
    return dest;
}


/*****************************************/
/*			                             */
/*     strncpy function  for WS 2        */
/*					                     */
/*****************************************/

char *StrnCpy(char *dest, const char *src, size_t n)
{
    char temp[n + 1];
    const char *runner = src;
    int i = 0;
    
    while (i < n && '\0' != *runner)
	{
        temp[i] = *runner;
        ++runner;
        ++i;
    }    
    
    temp[i] = '\0';    
    dest = temp;    
    
    return dest;
}

/*****************************************/
/*			                             */
/*     strcasecmp function for WS 2      */
/*					                     */
/*****************************************/

int StrCaseCmp(const char *s1, const char *s2)
{
    const char *runner1 = s1;
    const char *runner2 = s2;
    int return_val = 0;    
        
    while (tolower(*runner1) == tolower(*runner2) && 
                                '\0' != *runner1)
    {
        ++runner1;
        ++runner2;
    }
    
    if(*runner1 > *runner2)
    {
        return_val = 1;    
    }
    
    else if(*runner1 < *runner2)
    {
        return_val = -1;
    } 
    
    return (return_val);
}

/*****************************************/
/*			                             */
/*     strchr function for WS 2          */
/*					                     */
/*****************************************/

char *StrChr(const char *s, int c)
{
    const char *runner = s; 
    char *temp = NULL;
   
    while (c != *runner && '\0' != *runner)
    {
        ++runner;            
    }
    
    if('\0' == *runner)
    {
        return NULL;        
    }

    return(StrCpy(temp, runner));
}













