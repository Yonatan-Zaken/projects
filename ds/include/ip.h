#ifndef __IP_H__
#define __IP_H__

#define ADDRESS_SIZE_IN_BYTES 4

char *IpAddressToBinary(unsigned char ip_address[], char *buffer);

int IpIsSame(unsigned char ip1[], unsigned char ip2[]);

#endif
