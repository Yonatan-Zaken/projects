/*********************************/
/*   			             	 */
/*				                 */
/* Implement file work sheet 3   */
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
#include "work3.h"

char **CopyEnv(const char **buffer)
{
    const char **runner = buffer;
    char **copy = NULL;
    int str_size = 0;
    int i = 0;
    
    while(NULL != *runner)
    {
        printf("line %d length : %ld\n", i, strlen(*runner));
        str_size = strlen(*runner) + 1;
        *copy = (char*)malloc(sizeof(char) * str_size);
        strcpy(*copy, *runner);
        ++runner;
        ++i; 
    }
    
    runner = buffer;
     
    return copy;
}


void PrintEnv(const char **buffer)
{
    const char **runner = buffer;
        
    while(NULL != *runner)
    {
        printf("%s\n", *runner);
        ++runner; 
    }
    
}





