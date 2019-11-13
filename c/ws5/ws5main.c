/*********************************/
/*   			             	 */
/*				                 */
/*   Main file work sheet 5      */
/*   Yonatan Zaken		         */
/*   Last Updated 12/11/19       */
<<<<<<< HEAD
/*   Reviewed by: Aviran         */   
=======
/*   Reviewed by: 		     */   
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557
/*			                   	 */
/*			  	                 */
/*********************************/

<<<<<<< HEAD
enum OP_STATUS {SUCCESS, FAIL_REMOVE, FAIL_COUNT, FAIL_APPEND, FAIL_PREPEND,  FAIL_CHRCMP, EXIT};
=======
enum OP_STATUS {SUCCESS, FAIL, EXIT};
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557

#include <stdio.h>
#include "ws5header.h"

<<<<<<< HEAD
int main()
{
    
    struct lut lut_arr[NUM_ELEM];
    
    /* Initialize array of structures */
    InitFunc(lut_arr);
    
    Infrastructure("ws5.txt", lut_arr);
    
=======

int main()
{
    
    FILE *fp = fopen("ws5.txt", "a");
    
    if (NULL == fp)
    {
        printf("Can't open file.\n");
        return 0;
    }
    
    printf("%d\n", AddToFile("akuna matata",fp));
    
    
     
        
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557
    return 0;
}
