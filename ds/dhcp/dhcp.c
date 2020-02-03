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
#define BITS_IN_BYTE 8
#define RESERVED_ADDRESSES 3
#define MASK 0XFFU
#define LSB 0x01U

#define INDEX(height) ((BITS_IN_IP - height) / BITS_IN_BYTE)

struct DHCP
{
    trie_t *trie;
    ip_t subnet_mask;
    size_t available_bits;
};

static status_t ReservedAddressIMP(trie_t *trie)
{
    ip_t min_address = {0, 0, 0 ,0};
    ip_t max_address = {255, 255, 255, 255};
    ip_t before_max_address = {255, 255, 255, 254};
    
    assert(NULL != trie);
    
    if (SUCCESS != TrieInsert(trie, min_address))
    {
        return FAIL;
    }
    
    if (SUCCESS != TrieInsert(trie, max_address))
    {
        return FAIL;
    }
    
    if (SUCCESS != TrieInsert(trie, before_max_address))
    {
        return FAIL;
    }
    
    return SUCCESS;
}

static status_t CheckSubnetIMP(ip_t ip_address, size_t height)
{
    while (0 < height)
    {
        if(0 != (*(ip_address + (BITS_IN_IP - height) / BITS_IN_BYTE) & 
                             (LSB << ((height - 1) % BITS_IN_BYTE))))
        {
            return FAIL;
        }
        
        --height;
    }        
    
    return SUCCESS;
}

dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits)
{
    dhcp_t *dhcp = malloc(sizeof(*dhcp));
    if (NULL != dhcp)
    {
        dhcp->trie = TrieCreate(BITS_IN_IP - subnet_mask_reserved_bits);
        if (NULL == dhcp->trie)
        {
            free(dhcp); dhcp = NULL;
            return NULL;
        }
    }
    
    memcpy(dhcp->subnet_mask, subnet_mask, ADDRESS_SIZE_IN_BYTES);
    dhcp->available_bits = BITS_IN_IP - subnet_mask_reserved_bits;
    
    assert(FAIL != CheckSubnetIMP(subnet_mask, dhcp->available_bits));
    
    if (FAIL == ReservedAddressIMP(dhcp->trie))
    {
        free(dhcp); dhcp = NULL;
        return NULL;    
    }
    
    return dhcp;
}

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    TrieDestroy(dhcp->trie);
    free(dhcp); dhcp = NULL;
}

static status_t CheckRequestedIMP(dhcp_t *dhcp, ip_t requested_ip)
{
    ip_t requested = {0};
    size_t height = 0;
    size_t shift_holder = 0;
    
    height = dhcp->available_bits;
    shift_holder = height % BITS_IN_BYTE;
    memcpy(requested, requested_ip, ADDRESS_SIZE_IN_BYTES);
    
    while (0 < height)
    {
        shift_holder = height % BITS_IN_BYTE;
        if (0 == shift_holder)
        {
            *(requested + (BITS_IN_IP - height) / BITS_IN_BYTE) &= 0;
            height -= BITS_IN_BYTE;    
        }
        else
        {
            *(requested + (BITS_IN_IP - height) / BITS_IN_BYTE) = 
            (*(requested + (BITS_IN_IP - height) / BITS_IN_BYTE) >> shift_holder)
            << shift_holder;
            height -= shift_holder;
        }      
    }
    return !(0 == memcmp(requested, dhcp->subnet_mask, ADDRESS_SIZE_IN_BYTES));
}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{ 
    assert(NULL != dhcp);
    
    memcpy(allocated_ip, requested_ip, ADDRESS_SIZE_IN_BYTES);
    
    assert(FAIL != CheckRequestedIMP(dhcp, requested_ip));
    
    if (!TrieIsAvailable(dhcp->trie, requested_ip))
    {
         TrieNextAvailable(dhcp->trie, allocated_ip);
         if (FAIL == TrieInsert(dhcp->trie, allocated_ip))
         {
             return FAIL_TO_ALLOC;
         }  
         return NOT_AS_REQUESTED;
    }
    
    if (FAIL == TrieInsert(dhcp->trie, allocated_ip))
    {
        return FAIL_TO_ALLOC;
    }
        
    return AS_REQUESTED; 
}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{ 
    assert(NULL != dhcp);
                    
    TrieFreeLeaf(dhcp->trie, ip_address);
    return ADDRESS_FOUND;
}

size_t DhcpCountFree(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    return (pow(2, dhcp->available_bits) - TrieCountLeafs(dhcp->trie)); 
}
