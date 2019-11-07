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
    char **copy;
    char **header;
    const char **temp = buffer;
    int buff_size = 0;

    buff_size = BufferSize(buffer) - 1;
    printf("%d\n", buff_size);
    
    copy = (char**)calloc(buff_size, sizeof(char*));
    header = copy;
    
    while(0 < buff_size)
    {
        *copy = StrDup(*temp);
        StringToLower(*copy);
        ++temp;
        ++copy;
        --buff_size;
    }
         
    temp = buffer;
    copy = header;
    
    return copy; 
}


void PrintEnv(const char **buffer) /* PROBLEM WITH LAST PRINT IN LOOP */
{
    const char **runner = buffer;
    int buff_size = 0;
    buff_size = BufferSize(runner);  
    printf("first call: %d\n", buff_size);
    while (0 < buff_size)
    {
        printf("%s\n", *runner);
        ++runner;
        --buff_size;
    } 
}

void StringToLower(char *string)
{
    char *runner = string;
    
    while ('\0' != *runner)
    {
        *runner = tolower(*runner);
        ++runner;
    }
}

int BufferSize(const char **buffer)
{
    int count = 0;
    const char **runner = buffer;
    
    while (NULL != *runner)
    {
        ++runner;
        ++count;
    }
    
    return count;
}

char *StrDup(const char* s)
{
    int str_size = strlen(s) + 1; 
    
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


void CleanEnvCopy(char **buffer)
{
    char **runner = buffer;
    int buff_size = BufferSize((const char**)runner);
    
    while(0 < buff_size)
    {
        free(*runner);
        *runner = NULL;
        ++runner;
        --buff_size;
    }    
    
    free(runner);
    buffer = NULL;
}






