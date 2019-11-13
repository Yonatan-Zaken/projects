/*********************************/
/*   			             	 */
/*				                 */
/*   Main file work sheet 5      */
/*   Yonatan Zaken		         */
/*   Last Updated 12/11/19       */
/*   Reviewed by: 		     */   
/*			                   	 */
/*			  	                 */
/*********************************/

enum OP_STATUS {SUCCESS, FAIL, EXIT};


#include <stdio.h>
#include "ws5header.h"


int main()
{
    
    struct lut lut_arr[NUM_ELEM];
    
    InitFunc(lut_arr);
    
    IterationFunc("ws5.txt", lut_arr);
    
    
    
    return 0;
}
