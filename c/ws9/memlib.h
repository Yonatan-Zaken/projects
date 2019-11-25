/*********************************/
/*   			             	 */
/*   Header file work sheet 9    */
/*   Yonatan Zaken		         */
/*   Last Updated 24/11/19       */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*********************************/

#ifndef __MEMLIB_H__
#define __MEMLIB_H__

#include <stdio.h>    /* printf */
#include <string.h>   /* strlen, strcmp */
#include <stdlib.h>   /* atoi */
#include <assert.h>   

#define WORD_IN_BYTES 8 

#define ASCII_ZERO 48
#define ASCII_CHAR 55

#define IS_LITTLE_ENDIAN(x)    (*(char*)(&x) == (0xFF & x)) ?\
                              printf("Endianness is Little Endian.\n") :\
                              printf("Endianness is Big Endian.\n");

void *MyMemset(void *str, int c, size_t n);
void *MyMemcpy(void *dest, const void *src, size_t n);
void *MyMemmove(void *dest, const void *src, size_t n);
void IsLittleEndian(void);
void TestFunc(int condition, const char *message);

int MyAtoi(const char *str, int base);
int CheckThreeArrays(char array1[], char array2[], char array3[], int size1, int size2, int size3);

char *MyItoa(int num, char *buffer, int base);



#endif
