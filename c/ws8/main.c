/*********************************/
/*   			             	 */
/*   Main file work sheet 8      */
/*   Yonatan Zaken		         */
/*   Last Updated 20/11/19       */
/*   Reviewed by: Yoav Hattav    */   
/*			                   	 */
/*********************************/

#include "structs.h"

int main()
{
    int result = 0;
    
    /* Initialize a struct of arrays */
    types_and_oper inf_arr[3];

    /* This function initializes the members of the structure */
    /* in each element of the array                           */
    Initialize(inf_arr);
    
    result = Infrastructure(inf_arr);
    
    return 0;
}
