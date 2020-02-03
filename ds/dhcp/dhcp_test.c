/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   dhcp                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 30/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "dhcp.h"

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

static void PrintIP(ip_t ip)
{
    size_t i = 0;
    
    for (i = 0; i < 4; ++i)
    {
        printf("%u.", ip[i]);    
    }
}

static void DHCPTest1()
{
    ip_t subnet_mask = {192,50,72,0};
    ip_t requested_ip = {192, 50, 72, 0};
    size_t reserved_bits = 30;
    ip_t allocated_ip = {0};
    
    dhcp_t *dhcp = DhcpCreate(subnet_mask, reserved_bits);

    RUN_TEST(1 == DhcpCountFree(dhcp), "countfree");

    DhcpAllocIp(dhcp, requested_ip, allocated_ip);
    PrintIP(allocated_ip);

    DhcpDestroy(dhcp);
    printf("\n\n");
}

int main()
{
    DHCPTest1();
    
    return 0;
}
