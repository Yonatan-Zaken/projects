/*********************************/
/*   			             	 */
/*				                 */
/*Implementing file work sheet 3 */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by: Ben            */   
/*			                   	 */
/*			  	                 */
/*********************************/

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"

static void *MyMalloc(size_t n, int flag, int random_num, int iteration);

/*****************************************/
/*			                             */
/*     CopyEnv function for WS 3         */
/*					                     */
/*****************************************/

/* This function copies the environment variables to buffer*/
char **CopyEnv(const char **buffer, int flag)
{
    /* random number related variable */
    time_t t;
    
    const char **temp = buffer;
    char **copy;       /* This is the pointer to the copied variables */
    char **header;     /* This pointer is used to rewind copy in line 52 */     
    int buff_size = 0;
    int string_size = 0;
    int random_num = 0;
    
    /* Check if buffer points to \0 in debug mode */
    assert(NULL != temp); 
    
    buff_size = BufferSize(temp) - 1;
    
    /* Lines 48 + 49 generate random number for MyMalloc use */
    srand((unsigned) time(&t));
    random_num = rand() % buff_size + 1;
    
    /* Allocate memory for pointer to pointer */
    copy = (char**)calloc(buff_size, sizeof(char*));
    
    if (NULL == copy)
    {
        return NULL;
    }
    
    header = copy;
    
    while(0 < buff_size)
    {
        string_size = strlen(*temp) + 1;
        
        /* Allocate memory before copying strings */
        *copy = (char*)MyMalloc(string_size, flag, random_num, buff_size); 
        
        if (NULL == *copy)
        {
            printf("Can't allocat memory.");
            copy = header;
            CleanEnvCopy(copy);
            return NULL;
        }
        
        StrCpy(*copy, (char*)*temp);   /* <-- Copy strings from buffer */
               
       
        ++temp;
        ++copy;
        --buff_size;
    }
         
    temp = buffer;
    copy = header;
    
    return copy; 
}

/*****************************************/
/*			                             */
/*     PrintEnv function for WS 3        */
/*					                     */
/*****************************************/

/* This function prints the copied environment variables from the argument*/
void PrintEnv(const char **buffer) 
{
    const char **runner = buffer;
    int buff_size = 0;
    
    /* Check if buffer points to \0 in debug mode */
    assert(NULL != runner); 
    
    buff_size = BufferSize(runner);  
    
    while (0 < buff_size)
    {
        printf("%s\n", *runner);
        ++runner;
        --buff_size;
    } 
}


/*****************************************/
/*			                             */
/*     BufferSize function for WS 3      */
/*					                     */
/*****************************************/

/* Counts the buffer size */ 
int BufferSize(const char **buffer)
{
    const char **runner = buffer;
    int count = 0;
    
    /* Check if buffer points to \0 in debug mode */
    assert(NULL != runner);
    
    while (NULL != *runner)
    {
        ++runner;
        ++count;
    }
    
    return count;
}

/*****************************************/
/*			                             */
/*    CleanEnvCopy function for WS 3     */
/*					                     */
/*****************************************/

/* This function deallocates all the memory we allocated to store variables */
void CleanEnvCopy(char **buffer)
{
    char **runner = buffer;
    int buff_size = BufferSize((const char**)runner);
    
    /* Check if buffer points to \0 in debug mode */
    assert(NULL != buffer);
    
    while(0 < buff_size)
    {
        free(*runner);
        *runner = NULL;
        ++runner;
        --buff_size;
    }    
    
    free(buffer);
    buffer = NULL;
}

/*****************************************/
/*			                             */
/*    MyMalloc function for WS 3         */
/*					                     */
/*****************************************/

/* Wrapper function */

static void *MyMalloc(size_t n, int flag, int random_num, int iteration)
{
    void *ptr;
    
    if(0 != flag && iteration == random_num)
    { 
       ptr = NULL;
       return ptr;
    }
    
    else
    {
        ptr = malloc(n);
    }
    
    return ptr;
}


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
        *runner1 = tolower(*runner1);  /* <-- Convert strings to lowercase */
        ++runner1;     
        ++runner2;    
    }    
    
    *runner1 = '\0';        
    
    return dest;
}














