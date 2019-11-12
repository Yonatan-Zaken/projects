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
        enum OP_STATUS(*compare_ptr)(const char *, const char *);
        enum OP_STATUS(*op_ptr)(const char *, FILE *);
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

enum OP_STATUS ExitProg(const char *str, FILE *fp)
{
    printf("Exiting program...\n");
    return EXIT;
}

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


enum OP_STATUS Compare(const char *str, const char *usr_input)
{
    int is_equal = 0;
    
    is_equal = strcmp(str, usr_input);
    
    if (SUCCESS == is_equal)
    {
        return SUCCESS;
    }
    
    return FAIL;
}


enum OP_STATUS AddToFile(const char *str, FILE *fp)
{


}

















