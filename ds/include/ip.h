#ifndef __IP_H__
#define __IP_H__

#define ADDRESS_SIZE_IN_BYTES 4

char *IpConvertAddress(unsigned char ip_address[], char *dest);

int IpIsSame(unsigned char ip1[], unsigned char ip2[]);

#endif
