/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   ip                          */
/*   Author: Yonatan Zaken       */
/*   Last Updated 30/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "ip.h"

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

static void IpTest1()
{
    unsigned char arr[4] = {5, 5, 8, 8};
    unsigned char ip1[4] = {232, 232, 199, 252};
    unsigned char ip2[4] = {232, 232, 199, 252};
    char buffer[33] = {0};
    
    printf("%s\n", IpConvertToBinary(arr, buffer));
    printf("%d\n", IpIsSame(ip1, ip2));

}

int main()
{
    IpTest1();

    return 0;
}
