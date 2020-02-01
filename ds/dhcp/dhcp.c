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
#include <alloca.h> /* alloca */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <math.h> /* pow */

#include "ip.h"
#include "trie.h"
#include "dhcp.h"

#define BITS_IN_IP 32
#define RESERVED_ADDRESSES 3

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
    assert(NULL != dhcp);
    
}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{
    char *ip_buffer = NULL;
    
    assert(NULL != dhcp);
    
    ip_buffer = (char *)alloca(sizeof(char) * (BITS_IN_IP + 1));
    ip_buffer = IpConvertAddress(ip_address, ip_buffer) + 
                     (BITS_IN_IP - dhcp->available_bits); 
                     
    if (FALSE == TrieIsExist(dhcp->trie, ip_buffer))
    {
        return ADDRESS_NOT_FOUND;         
    }
    
    TrieFreeLeaf(dhcp->trie, ip_buffer);
    return ADDRESS_FOUND;
}

size_t DhcpCountFree(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    return (pow(2, dhcp->available_bits) - RESERVED_ADDRESSES - 
                                    TrieCountLeafs(dhcp->trie));
}
