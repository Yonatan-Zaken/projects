/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   AVL Tree                    */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/1/20        */
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */
#include <assert.h>

#include "avl.h"


#define UNUSED(x) (void)(x)

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

int main()
{
    

    return 0;
}
