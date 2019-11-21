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
    result = Initialize(inf_arr);
    
    if (1 == result)
    {
        printf("Fail to allocate memory to inf_arr[2].data_type.");
        return 1;
    }
    
    result = Infrastructure(inf_arr);
    
    if (1 == result)
    {
        printf("Fail to re-allocate memory to inf_arr[2].data_type.");
        return 1;
    }
    
    return 0;
}
