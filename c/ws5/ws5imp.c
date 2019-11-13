/*********************************/
/*   			             	 */
/*Implementing file work sheet 5 */
/*   Yonatan Zaken		         */
/*   Last Updated 12/11/19       */
<<<<<<< HEAD
/*   Reviewed by: Aviran         */   
/*			                   	 */
/*********************************/


enum OP_STATUS {SUCCESS, FAIL_REMOVE, FAIL_COUNT, FAIL_APPEND, FAIL_PREPEND,  FAIL_CHRCMP, EXIT};
=======
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/

/* success = 0, fail = 1, exit = 2 */
enum OP_STATUS {SUCCESS, FAIL, EXIT};
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
<<<<<<< HEAD
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
       
    while (SUCCESS == status)
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

enum OP_STATUS ExitProg(const char *file_name, const char *str)
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

enum OP_STATUS RemoveFile(const char *file_name, const char *str)
{
    int is_removed = 0;
    
    UNUSED (str);
    
    assert (NULL != file_name);
    
    is_removed = remove(file_name);
=======
#include "ws5header.h"

/* This function initializes the struct */
/* and the array of this structure type */

void  InitFunc()
{
    struct lut
    {
        char *name;
        int (*compare_ptr)(const char *, const char *);
        enum OP_STATUS (*op_ptr)(const char *, FILE *);
    };
    
    struct lut lut_arr[5];
    
    lut_arr[0].name = "-exit";
    lut_arr[0].compare_ptr = &Compare;
    lut_arr[0].op_ptr = &ExitProg;
    
    lut_arr[1].name = "-remove";
    lut_arr[1].compare_ptr = &Compare;
    lut_arr[1].op_ptr = &RemoveFile;
    
    lut_arr[2].name = "-count";
    lut_arr[2].compare_ptr = &Compare;
    lut_arr[2].op_ptr = &CountLines;
    
    lut_arr[3].name = "<";
    lut_arr[3].compare_ptr = &Compare;
    lut_arr[3].compare_ptr = &AddToTop;
    
    lut_arr[4].name = "add";
    lut_arr[4].compare_ptr = NULL;
    lut_arr[4].op_ptr = &AddToBottom;
    
    
}

void IterationFunc(const char *file_name)
{
    
    char input[100]; 
    int return_val = 0;
    int i = 0;
    
    
    while (EXIT != return_val)
    {
        gets(input);
        
        for (i = 0; i < 5; i++)
        {
            
        }
          
    }

}



/* If this function is called it exits the program */

enum OP_STATUS ExitProg(const char *str, FILE *fp)
{
    printf("Exiting program...\n");
    return EXIT;
}

/* If this program is called it closes the file     */
/* it gets as argument and deletes it. The function */
/* returns SUCCESS if the file was removed.         */ 

enum OP_STATUS RemoveFile(const char *str, FILE *fp)
{
    int is_removed = 0;
    
    fclose(fp);
    fp = NULL;
    
    is_removed = remove(str);
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557
    
    if(SUCCESS == is_removed)
    {
        return SUCCESS;
    }
    
<<<<<<< HEAD
    return FAIL_REMOVE;
}

/************************************************/
/* This function opens the file and counts the  */
/* number of lines in the file.                 */
/************************************************/

enum OP_STATUS CountLines(const char *file_name, const char *str)
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
=======
    return FAIL;
}

/* This function gets a pointer to file and */
/* counts the number of lines in the file.  */
/* New line without strings are also counted*/

enum OP_STATUS CountLines(const char *str, FILE *fp)
{
    int return_val = 0;
    int count = 0;
    char c = 0;
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557
    
    while (EOF != (c = fgetc(fp)))
    {
        if ('\n' == c)
        {
            ++count;
        }        
    }
    
<<<<<<< HEAD
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

enum OP_STATUS Append(const char *file_name, const char *str)
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

enum OP_STATUS Preppend(const char *file_name, const char *str)
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
=======
    /* additional ++ on count because EOF won't count last line */
    printf("There are %d lines in %s\n", ++count, str); 
    
    return_val = fclose(fp);
    fp = NULL;
    
    return ;
}

/* This function gets 2 strings and compares them */
/* The function returns SUCCESS if they are equal */

int Compare(const char *str, const char *usr_input)
{
    int is_equal = 1;
    
    is_equal = strcmp(str, usr_input);
    
    if (0 == is_equal)
    {
        return SUCCESS;
    }
    
    return is_equal;
}


enum OP_STATUS AddToBottom(const char *str, FILE *fp)
{
    int return_val = 0;
    
    fflush(fp);
    fputs(str, fp);
    fputs("\n",fp);
    
    return_val = fclose(fp);
    fp = NULL;
    
    return return_val;
    
}

enum OP_STATUS AddToTop(const char *str, FILE *fp)
{   
        ++str;
        FILE *fp2 = fopen("temp.txt");
            
        
    
        
}








>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557







