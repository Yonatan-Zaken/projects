/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Heap                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 20/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "heapify.h"

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

int IsMatch(void *data1, void *data2)
{
    return (*(int*)data1 == *(int*)data2);
}

int CompareFunc(const void *data1, const void *data2, void *param)
{
    return (*(int*)data1 - *(int*)data2);
}

int main()
{

    
    return 0;
}
