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
    printf("\n");
}

static void DHCPTest1()
{
    dhcp_t *dhcp = NULL;
    ip_t subnet_mask = {192,50,72,0};
    ip_t requested_ip = {192, 50, 72, 0};
    ip_t allocated_ip = {0};
        
    printf("DHCP Test1:\n");
    dhcp = DhcpCreate(subnet_mask, 30);

    RUN_TEST(1 == DhcpCountFree(dhcp), "countfree");

    DhcpAllocIp(dhcp, requested_ip, allocated_ip);
    PrintIP(allocated_ip);

    DhcpDestroy(dhcp);
    printf("\n\n");
}

static void DHCPTest2()
{
    dhcp_t *dhcp = NULL;
    ip_t subnet_mask = {200,15,150,0};
    ip_t request1 = {200, 15, 150, 1},
         request2 = {200, 15, 150, 2},
         request3 = {200, 15, 150, 4},
         request4 = {200, 15, 150, 7},
         request5 = {200, 15, 151, 7},
         request6 = {200, 15, 150, 6};
    ip_t allocated_ip = {0};
        
    printf("DHCP Test2:\n");
    dhcp = DhcpCreate(subnet_mask, 29);

    RUN_TEST(5 == DhcpCountFree(dhcp), "countfree");

    RUN_TEST(AS_REQUESTED == DhcpAllocIp(dhcp, request1, allocated_ip), "Alloc");
    RUN_TEST(4 == DhcpCountFree(dhcp), "countfree");
    PrintIP(allocated_ip);
    
    RUN_TEST(NOT_AS_REQUESTED == DhcpAllocIp(dhcp, request1, allocated_ip), "Alloc");
    RUN_TEST(3 == DhcpCountFree(dhcp), "countfree");
    PrintIP(allocated_ip);
    
    RUN_TEST(AS_REQUESTED == DhcpAllocIp(dhcp, request3, allocated_ip), "Alloc");
    RUN_TEST(2 == DhcpCountFree(dhcp), "countfree");
    PrintIP(allocated_ip);
    
    RUN_TEST(NOT_AS_REQUESTED == DhcpAllocIp(dhcp, request3, allocated_ip), "Alloc");
    RUN_TEST(1 == DhcpCountFree(dhcp), "countfree");
    PrintIP(allocated_ip);
    
    RUN_TEST(NOT_AS_REQUESTED == DhcpAllocIp(dhcp, request4, allocated_ip), "Alloc");
    RUN_TEST(0 == DhcpCountFree(dhcp), "countfree");
    PrintIP(allocated_ip);
    
    DhcpFreeIp(dhcp, request1);
    RUN_TEST(1 == DhcpCountFree(dhcp), "countfree");
    
    RUN_TEST(ADDRESS_NOT_FOUND == DhcpFreeIp(dhcp, request5), "free");
    RUN_TEST(ADDRESS_FOUND == DhcpFreeIp(dhcp, request2), "free");
    RUN_TEST(2 == DhcpCountFree(dhcp), "countfree");
    
    RUN_TEST(AS_REQUESTED == DhcpAllocIp(dhcp, request2, allocated_ip), "Alloc");
    RUN_TEST(1 == DhcpCountFree(dhcp), "countfree");
    PrintIP(allocated_ip);
    
    RUN_TEST(NOT_AS_REQUESTED == DhcpAllocIp(dhcp, request6, allocated_ip), "Alloc");
    RUN_TEST(0 == DhcpCountFree(dhcp), "countfree");
    
    RUN_TEST(FAIL_TO_ALLOC == DhcpAllocIp(dhcp, request6, allocated_ip), "Alloc");
    
    DhcpDestroy(dhcp);
    printf("\n\n");
}

int main()
{
    DHCPTest1();
    DHCPTest2();
    
    return 0;
}
