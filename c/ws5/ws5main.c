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
    
    FILE *fp = fopen("ws5.txt", "a");
    
    if (NULL == fp)
    {
        printf("Can't open file.\n");
        return 0;
    }
    
    printf("%d\n", AddToFile("akuna matata",fp));
    
    
     
        
    return 0;
}
