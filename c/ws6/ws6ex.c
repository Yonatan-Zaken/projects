/*********************************/
/*   			             	 */
/*Implementing file work sheet 6 */
/*   Yonatan Zaken		         */
/*   Last Updated 14/11/19       */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include "ws6.h"

/* This function returns the result of */
/* the computation x AND (2 XOR y)     */

long Pow2 (unsigned int x, unsigned int y)
{
    return (x & (2 ^ y));      
}

/* This function gets a positive number and returns a   */
/* value that indicates if it's a power of 2 via loop   */

int NPow2Loop (unsigned int n)
{
    int is_pow2 = 1;    
    
    if (0 == n)
    {
        is_pow2 = 0;
        return 1;
    }
    
    while (1 ^ n)
    {
        if (1 & n)
        {
            is_pow2 = 0;
        }
        
        n = n >> 1;
    }
      
    return is_pow2;
}

/* This function gets a positive number and returns a   */
/* value that indicates if it's a power of 2 via loop   */

int NPow2 (unsigned int n)
{
        
        
        
}














