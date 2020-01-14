/*********************************/
/*   			             	 */
/*   Recursion                   */
/*   Author: Yonatan Zaken       */
/*   Last Updated 14/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/
#include <string.h> /* strlen */

#include "recursion.h"

size_t RecFib(size_t position)
{
    if(0 == position || 1 == position)
    {
        return 1;
    }    
        
    return (RecFib(position - 2) + RecFib(position - 1));
}

size_t RecStrlen(const char *str)
{
    size_t size = 0;
    
    if ('\0' == *str)
    {
        return 0;
    }
    
    size = RecStrlen(str + 1) + 1;
    
    return size;
}

int RecStrcmp(const char *s1, const char *s2)
{
    int result = 0;
    
    if ((*s1 != *s2) || ('\0' == *s1))
    {
        return (*s1 - *s2);
    }
    
    result = RecStrcmp(s1 + 1, s2 + 1);
    return result;
}

char *RecStrcpy(char *dest, const char *src)
{
    if ('\0' != *src)
    {
        RecStrcpy(dest + 1, src + 1);
    }
    
    *dest = *src;
    return dest;
}

char *RecStrcat(char *dest, const char *src)
{


}
