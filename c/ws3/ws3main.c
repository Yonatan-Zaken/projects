/*********************************/
/*   			             	 */
/*				                 */
/*   Main file work sheet 3      */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by: Ben		     */   
/*			                   	 */
/*			  	                 */
/*********************************/

#include <stdio.h>

#include "environment.h"

int main(int argc, char *argv[], char *envp[])
{
    char **buffer = envp; 
    
    /* Change flag to 1 to test NULL return from malloc */
    buffer = CopyEnv((const char**)buffer, 0);  
    
    if(NULL == buffer)
    {
        printf("No memory allocated, can't print variables.\n");
        return 1;
    }
    
    PrintEnv((const char**)buffer);             /* print copied variables */
    CleanEnvCopy(buffer);                       /* de-allocate memory */
    
    return 0;
}
