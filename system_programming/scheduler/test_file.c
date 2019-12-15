/*********************************/
/*   			             	 */
/*   System Programming          */
/*   UID                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/12/19       */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "scheduler.h"

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
