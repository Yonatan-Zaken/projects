/*********************************/
/*   			             	 */
/*   Main file DS 9              */
/*   Yonatan Zaken		         */
/*   Last Updated 11/12/19       */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "sortedlist.h" /* sorted list functions */
#include "priorityqueue.h" /* priority list functions */

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
