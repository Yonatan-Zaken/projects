/*********************************/
/*   			             	 */
/*Implementing file work sheet 5 */
/*   Yonatan Zaken		         */
/*   Last Updated 12/11/19       */
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ws5header.h"

/* success = 0 and fail = 1 */

typedef enum op_status{success, fail} op_status;
op_status status;

/* This function initializes the struct */
/* and the array of this structure type */

int InitFunc()
{
    struct lut
    {
        char *str;
        int (*compare_ptr)(const char *, const char *);
        enum op_status(*op_ptr)(const char *, FILE *);
    };
    
    struct lut lut_arr[5];    
    
    
    
}


op_status ExitProg(const char *str)
{
    
    
    
}



















