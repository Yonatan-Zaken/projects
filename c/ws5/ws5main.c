/*********************************/
/*   			             	 */
/*   Main file work sheet 5      */
/*   Yonatan Zaken		         */
/*   Last Updated 13/11/19       */
/*   Reviewed by: Aviran         */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include "ws5header.h"

int main()
{
    
    struct lut lut_arr[NUM_ELEM];
    
    /* Initialize array of structures */
    InitFunc(lut_arr);
    
    Infrastructure("ws5.txt", lut_arr);
    
    return 0;
}
