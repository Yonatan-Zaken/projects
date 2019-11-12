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
    
    FILE *fp = fopen("ws5.txt", "r");
    fprintf(fp, "%s", "This is better\nWhat\nWait what?\nHello Hello");
    
    
    CountLines("ws5.txt",fp);
    
        
    return 0;
}
