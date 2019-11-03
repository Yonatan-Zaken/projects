#include <stdio.h>
#include <assert.h>

/*****************************************/
/*			                 */
/*     strlen function  for WS 2         */
/*					 */
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
/*			                 */
/*     strcmp function  for WS 2         */
/*					 */
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
    const char *runner = src;
    char temp[StrLen(src)+1] = {};
        
    while( '\0' != *runner)
    {
        *temp =     
    }    

}








