/*********************************/
/*   			             	 */
/*Implementing file work sheet 5 */
/*   Yonatan Zaken		         */
/*   Last Updated 13/11/19       */
/*   Reviewed by: Aviran         */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "ws5header.h"

/******************************************/
/* This function initializes the struct   */
/* and the array of this structure type   */
/******************************************/

void InitFunc(struct lut lut_arr[])
{
    
    lut_arr[0].name = "-exit";
    lut_arr[0].compare_ptr = &StrCmp;
    lut_arr[0].op_ptr = &ExitProg;
    
    lut_arr[1].name = "-remove";
    lut_arr[1].compare_ptr = &StrCmp;
    lut_arr[1].op_ptr = &RemoveFile;
    
    lut_arr[2].name = "-count";
    lut_arr[2].compare_ptr = &StrCmp;
    lut_arr[2].op_ptr = &CountLines;
    
    lut_arr[3].name = "<";
    lut_arr[3].compare_ptr = &ChrCmp;
    lut_arr[3].op_ptr = &Preppend;
    
    lut_arr[4].name = "this string allways matches";
    lut_arr[4].compare_ptr = &AlwaysMatch;
    lut_arr[4].op_ptr = &Append;
       
}

/************************************************************/
/* This function operates the programs operating functions  */
/* by iterating through the array of structure type and     */
/* comparing the users input to the array elements name     */
/************************************************************/

void Infrastructure(const char *file_name, struct lut lut_arr[])
{
    char input[INPUT_SIZE];
    int i = 0;
    int status = 0;    
    
    assert(NULL != file_name);
    
    /* Think how to improve exit status       */
    /* considering if failure status returns  */   
    while (EXIT != status)
    {
        
        fgets(input, INPUT_SIZE, stdin);
       
        for (i = 0; i < NUM_ELEM; i++) 
        {
            
            status = lut_arr[i].compare_ptr(lut_arr[i].name, input);      
            
            if (SUCCESS == status)
            {
                status = lut_arr[i].op_ptr(file_name, input);
                break;
            }       
        }       
    }
}

/***************************************************/
/* If this function is called it exits the program */
/***************************************************/

OP_STATUS ExitProg(const char *file_name, const char *str)
{
    UNUSED(file_name);
    UNUSED(str);
    
    return EXIT;
}

/****************************************************/
/* If this program is called it closes the file     */
/* it gets as argument and deletes it. The function */
/* returns SUCCESS if the file was removed.         */ 
/****************************************************/

OP_STATUS RemoveFile(const char *file_name, const char *str)
{
    int is_removed = 0;
    
    UNUSED (str);
    
    assert (NULL != file_name);
    
    is_removed = remove(file_name);
    
    if(SUCCESS == is_removed)
    {
        return SUCCESS;
    }
    
    return FAIL_REMOVE;
}

/************************************************/
/* This function opens the file and counts the  */
/* number of lines in the file.                 */
/************************************************/

OP_STATUS CountLines(const char *file_name, const char *str)
{
    
    int count = 0;
    char c = 0;
    FILE *fp = fopen(file_name, "r");
    
    UNUSED(str);
    assert (NULL != file_name);

    if (NULL == fp)
    {
        printf("Can't open file.\n");
        return FAIL_COUNT;
    }
    
    while (EOF != (c = fgetc(fp)))
    {
        if ('\n' == c)
        {
            ++count;
        }        
    }
    
    fclose(fp);
    fp = NULL;
    
    /* additional ++ on count because EOF won't count last line */
    printf("There are %d lines in %s\n", count, file_name); 
    
    return SUCCESS;
}


/*********************************************************/
/* This function opens the file and appends the string   */
/* from the input of the user to the bottom of the file  */
/*********************************************************/

OP_STATUS Append(const char *file_name, const char *str)
{
    
    FILE *fp = fopen(file_name, "a");
    
    assert (NULL != file_name);
    
    if (NULL == fp)
    {
        return FAIL_APPEND;
    }
    
    fputs(str, fp);
    
    fclose(fp);
    fp = NULL;
    
    return SUCCESS;  
}


/***********************************************/
/*This function gets a file name as argument   */
/* and appends the string from the user to the */ 
/* top of it                                   */
/***********************************************/

OP_STATUS Preppend(const char *file_name, const char *str)
{
    const char *runner = str;
    char c = 0;
    
    FILE *fp = fopen(file_name, "r");
    FILE *fp2 = fopen("temp.txt", "a");
    
    if (NULL == fp)
    {
        return FAIL_PREPEND;
    }
    
    if (NULL == fp2)
    {
        return FAIL_PREPEND;
    }
            
    assert (NULL != file_name); 
    assert (NULL != str);
    
    ++runner;
    fprintf(fp2, "%s", runner);
    
    
    while (EOF != (c = fgetc(fp)))
    {
        fputc(c, fp2);
    }
    
    fclose (fp);
    fp = NULL;
    
    fclose (fp2);
    fp2 = NULL;
    
    RemoveFile (file_name, str);
    rename ("temp.txt", file_name);
    
    return SUCCESS;
}

/*********************************************/
/* This functions returns SUCCESS as default */
/*********************************************/

int AlwaysMatch(const char *str, const char *usr_input)
{
    UNUSED(str);
    UNUSED(usr_input);
    
    return SUCCESS;
}

/**************************************************/
/* This function gets 2 strings and compares them */
/* The function returns SUCCESS if they are equal */
/**************************************************/

int StrCmp(const char *str, const char *usr_input)
{
    const char *runner1 = str;
    const char *runner2 = usr_input;
        
    /* Check if s1/s2 point to '\0' in debug mode */    
    assert(NULL != str);
    assert(NULL != usr_input);  
     
            
    while (*runner1 == *runner2 && '\0' != *(runner1+1))
    {
        ++runner1;
        ++runner2;
    }
    
    return (*runner1 - *runner2);
}

/*********************************************/
/* This function gets 2 strings and checks   */
/* if they both start with the character '<' */
/*********************************************/

int ChrCmp(const char *str, const char *usr_input)
{
    
    assert (NULL != str);
    assert (NULL != usr_input);
    
    if (*str == *usr_input)
    {
        return (*str - *usr_input);
    }    
    
    return FAIL_CHRCMP;
}







