/*********************************/
/*   			             	 */
/*   Main file work sheet 9      */
/*   Yonatan Zaken		         */
/*   Last Updated 21/11/19       */
/*   Reviewed by: Yoav Hattav    */   
/*			                   	 */
/*********************************/

#include "memlib.h"

int main()
{
    char str[30] = "helloworldhelloworld";    
    void *result = MyMemset(str, 'c', 18);
    
    if (NULL == result)
    {
        printf("n bytes exceed buffer size. aborting...\n");
        return 1;
    }
    
    printf("%s\n", (unsigned char*)result);
    
    return 0;
}

