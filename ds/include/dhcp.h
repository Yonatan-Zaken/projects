#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /*size_t*/

#define ADDRESS_SIZE_IN_BYTES 4 

typedef struct DHCP dhcp_t;

typedef unsigned char ip_t[ADDRESS_SIZE_IN_BYTES];

typedef enum 
{ 
    AS_REQUESTED,
    NOT_AS_REQUESTED, 
    FAIL_TO_ALLOC
} alc_status_t;

typedef enum 
{
    ADDRESS_FOUND, 
    ADDRESS_NOT_FOUND
} free_status_t;

/*
* DhcpCreate() - 
* Returns pointer to the Dhcp, will return NULL if failed. 
* @subnet_mask_reserved_bits: dhcp reserved bits in address. 
* ex: 255.255.255.0/24: the first 24 bits are dhcp reserved. 
* complexity of malloc();       
*/
dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits);

/*
* DhcpDetroy() -
* Destroys and frees dhcp from memory.
* undefined behaviour for @dhcp NULL pointer
* complexity: free();                  
*/
void DhcpDestroy(dhcp_t *dhcp);

/*
* DhcpAllocIp() -
* will try to allocat the @requested_ip and returnd the result to the actual @alocated_ip variable.
* @requested_ip 0.0.0.0: will generate next avilable address. 
* undefined behaviour for @dhcp NULL pointer.
* undefined behaviour for @requested_ip address out of range.  
* return value: 
    - AS_REQUESTED
    - NOT_AS_REQUESTED - alocate a different address than requested
    - FAIL_TO_ALLOC  
* 0.0.0.0, 255.255.255.255, 255.255.255.254: dhcp reserved - if requested undefined behaviour
* complexity: Olog(n)  
*/
alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip);

/*
* DhcpFreeIp() -
* frees the @ip_address from the dhcp
* undefined behaviour for @dhcp NULL pointer
* undefined behavior for freeing reserved addresses: 
* 0.0.0.0, 255.255.255.255, 255.255.255.254
* return value: 
    - ADDRESS_FOUND 
    - ADDRESS_NOT_FOUND   
* complexity: Olog(n)            
*/
free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address);

/*
* DhcpCountFree() -
* undefined behaviour for @dhcp NULL pointer 
* return the number of the available ip addresses in the subnet given range 
* complexity: O(n)          
*/
size_t DhcpCountFree(const dhcp_t *dhcp);

#endif
