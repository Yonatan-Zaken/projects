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

int InitFunc()
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
    
    lut_arr[3].name = "add";
    lut_arr[3].compare_ptr = NULL;
    lut_arr[3].op_ptr = &AddToFile;
    
    
}

void IterationFunc(const char *file_name)
{
    


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
    
    if(SUCCESS == is_removed)
    {
        return SUCCESS;
    }
    
    return FAIL;
}

/* This function gets a pointer to file and */
/* counts the number of lines in the file.  */
/* New line without strings are also counted*/

enum OP_STATUS CountLines(const char *str, FILE *fp)
{
    int count = 0;
    char c = 0;
    
    while (EOF != (c = fgetc(fp)))
    {
        if ('\n' == c)
        {
            ++count;
        }        
    }
    
    /* additional ++ on count because EOF won't count last line */
    printf("There are %d lines in %s\n", ++count, str); 
    
    fclose(fp);
    fp = NULL;
    
    
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

    if ('<' == *str)
    {
        ++str;
        FILE *fp2 = fopen("temp.txt");
            
        
    }
        
}















