/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   IP                          */
/*   Author: Yonatan Zaken       */
/*   Last Updated 30/1/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* strcat */

#include "ip.h"

#define BASE 2
#define ASCII_ZERO 48
#define BITS_IN_BYTE 8

#define MASK1 0x55555555
#define MASK2 0xaaaaaaaa
#define MASK3 0x33333333
#define MASK4 0xcccccccc
#define MASK5 0x0f0f0f0f
#define MASK6 0xf0f0f0f0

static char *NumToStringIMP(unsigned int num, char *buffer)
{
    char *runner = NULL;
    int remainder = 0;    
    size_t i = 0;
    
    assert(NULL != buffer);
    
    runner = buffer;
    
    for (i = 0; i < BITS_IN_BYTE; ++i)
    {
        remainder = num % BASE;        
        *runner = (remainder + ASCII_ZERO);
        num /= BASE;
        ++runner;    
    }
    
    *runner = '\0';
    return buffer;        
}

static unsigned char MirrorIMP(unsigned char bits)
{  
    bits = ((bits & MASK2) >> 1) | ((bits & MASK1) << 1);
    bits = ((bits & MASK4) >> 2) | ((bits & MASK3) << 2);
    bits = ((bits & MASK6) >> 4) | ((bits & MASK5) << 4);
    
    return bits;
}

char *IpConvertAddress(unsigned char ip_address[], char *dest)
{
    size_t i = 0; 
    char buffer[BITS_IN_BYTE + 1] = {0};
    
    assert(NULL != dest);
    
    for (i = 0; i < ADDRESS_SIZE_IN_BYTES; ++i)
    {
        strcat(dest, NumToStringIMP(MirrorIMP(ip_address[i]), buffer));
    }
    
    return dest;                                       
}

int IpIsSame(unsigned char ip1[], unsigned char ip2[])
{
    return !(memcmp(ip1, ip2, ADDRESS_SIZE_IN_BYTES));
}

