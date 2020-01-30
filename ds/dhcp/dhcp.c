/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   DHCP                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 30/1/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "ip.h"
#include "trie.h"
#include "dhcp.h"

#define BITS_IN_IP 32

struct DHCP
{
    trie_t *trie;
    ip_t subnet_mask;
    size_t available_bits;
};

dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits)
{
    dhcp_t *dhcp = malloc(sizeof(*dhcp));
    if (NULL != dhcp)
    {
        dhcp->trie = TrieCreate();
        if (NULL == dhcp->trie)
        {
            free(dhcp); dhcp = NULL;
            return NULL;
        }
    }
    
    memcpy(dhcp->subnet_mask, subnet_mask, ADDRESS_SIZE_IN_BYTES);
    dhcp->available_bits = BITS_IN_IP - subnet_mask_reserved_bits;
    return dhcp;
}

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    TrieDestroy(dhcp->trie);
    free(dhcp); dhcp = NULL;
}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{

}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{

}

size_t DhcpCountFree(const dhcp_t *dhcp)
{

}
