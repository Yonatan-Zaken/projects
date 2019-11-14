/*********************************/
/*   			             	 */
/*Implementing file work sheet 5 */
/*   Yonatan Zaken		         */
/*   Last Updated 14/11/19       */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include "ws6.h"

long Pow2 (unsigned int x, unsigned int y)
{
    return x & (2 ^ y);      
}

int NPow2 (unsigned int n)
{
    is_pow2 = 0;    
    
    while ((n & 1))
    {
        n >> 1;     
            
    }
      
}
