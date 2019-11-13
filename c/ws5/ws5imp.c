/*********************************/
/*   			             	 */
/*Implementing file work sheet 5 */
/*   Yonatan Zaken		         */
/*   Last Updated 12/11/19       */
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/

/* success = 0, fail = 1, exit = 2 */
enum OP_STATUS {SUCCESS, FAIL, EXIT};

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ws5header.h"

/* This function initializes the struct */
/* and the array of this structure type */

void InitFunc(struct lut lut_arr[])
{
    
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
    lut_arr[3].op_ptr = &AddToTop;
    
    lut_arr[4].name = "this string allways matches";
    lut_arr[4].compare_ptr = &AlwaysMatch;
    lut_arr[4].op_ptr = &AddToBottom;
    
    
    
}

void IterationFunc(const char *file_name, struct lut lut_arr[])
{
       
    char input[10];
    int i = 0;
    int status = 0;    
       
    while (EXIT != status)
    {
        fgets(input, sizeof(input), stdin);
        
        for (i = 0; i < NUM_ELEM; i++) 
        {
            
            status = lut_arr[i].compare_ptr(lut_arr[i].name, input);      
            
            if(SUCCESS == status)
            {
                lut_arr[i].op_ptr(file_name, input);
            }
            
                
        }       
    }
}



/* If this function is called it exits the program */

enum OP_STATUS ExitProg(const char *file_name, const char *str)
{
    printf("Exiting program...\n");
    return EXIT;
}

/* If this program is called it closes the file     */
/* it gets as argument and deletes it. The function */
/* returns SUCCESS if the file was removed.         */ 

enum OP_STATUS RemoveFile(const char *file_name, const char *str)
{
    int is_removed = 0;
   
    is_removed = remove(str);
    
    if(SUCCESS == is_removed)
    {
        return SUCCESS;
    }
    
    return FAIL;
}

/* This function opens the file and counts the */
/* number of lines in the file.                */

enum OP_STATUS CountLines(const char *file_name, const char *str)
{
    int return_val = 0;
    int count = 0;
    char c = 0;
    
    FILE *fp = fopen(str, "r");
    
    if (NULL == fp)
    {
        printf("Can't open file.\n");
        return FAIL;
    }
    
    while (EOF != (c = fgetc(fp)))
    {
        if ('\n' == c)
        {
            ++count;
        }        
    }
    
    return_val = fclose(fp);
    fp = NULL;
    
    /* additional ++ on count because EOF won't count last line */
    printf("There are %d lines in %s\n", ++count, str); 
    
    return SUCCESS;
}


/* This function opens the file and appends the string */
/* from the input of the user to the bottom of the file*/

enum OP_STATUS AddToBottom(const char *file_name, const char *str)
{
    int return_val = 0;
    
    FILE *fp = fopen(file_name, "a");
    
    fflush(fp);
    fputs(str, fp);
    fputs("\n",fp);
    
    return_val = fclose(fp);
    fp = NULL;
    
    return return_val;  
}


/*This function gets a file name as argument   */
/* and appends the string from the user to the */ 
/* top of it                                   */

enum OP_STATUS AddToTop(const char *file_name, const char *str)
{
    FILE *fp = fopen(file_name, "a");    
    
    if (NULL == fp)
    {
        printf("Can't open file.\n");
        return FAIL;
    }
    
    
     
}

int AlwaysMatch(const char *str, const char *usr_input)
{
    return 0;
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













