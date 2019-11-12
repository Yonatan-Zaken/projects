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
#include "ws5header.h"

/* This function initializes the struct */
/* and the array of this structure type */

int InitFunc()
{
    struct lut
    {
        char *str;
        int (*compare_ptr)(const char *, const char *);
        enum OP_STATUS(*op_ptr)(const char *, FILE *);
    };
    
    struct lut lut_arr[5];    
    
}

enum OP_STATUS ExitProg(const char *str, FILE *fp)
{
    
    
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





















