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
    int remove = 0;
    FILE *fp = fopen("ws5.txt", "r");
    remove = RemoveFile("ws5.txt", fp);
        
    return 0;
}
