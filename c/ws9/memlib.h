/*********************************/
/*   			             	 */
/*   Header file work sheet 9    */
/*   Yonatan Zaken		         */
/*   Last Updated 21/11/19       */
/*   Reviewed by: Yoav Hattav    */   
/*			                   	 */
/*********************************/

#ifndef __MEMLIB_H__
#define __MEMLIB_H__

#include <stdio.h>    /* printf */
#include <string.h>   /* strlen */
#include <stdlib.h>   /* atoi */

#define WORD_IN_BYTES 8 

#define IS_LITTLE_ENDIAN(x)    (*(char*)(&x) == (0xFF & x)) ?\
                              printf("Endianness is Little Endian.\n") :\
                              printf("Endianness is Big Endian.\n");

void *MyMemset(void *str, int c, size_t n);
void *MyMemcpy(void *dest, const void *src, size_t n);
void *MyMemmove(void *dest, const void *src, size_t n);
void IsLittleEndian(void);
void TestFunc(int condition, const char *message);
void CheckThreeArrays();

int MyAtoi(const char *str);

char *MyItoa(int num, char *buffer, int base);

#endif
