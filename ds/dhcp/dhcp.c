/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   DHCP                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 29/1/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stdlib.h>

#include "trie.h"

dhcp_t *DhcpCreate(ipt_t subnet_mask, size_t subnet_mask_reserved_bits)
{

}


void DhcpDetroy(dhct_t *dhcp)
{

}


alc_status_t DhcpAllocIp(dhcp_t *dhcp, ipt_t requested_ip, ip_t allocated_ip)
{

}


free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{

}

size_t DhcpCountFree(const dhcp_t *dhcp)
{

}
