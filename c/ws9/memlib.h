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

#define WORD_IN_BYTES 8 

#include <stdio.h>    /* printf */
#include <string.h>   /* strlen */
#include <stdlib.h>   /* atoi */

void *MyMemset(void *str, int c, size_t n);
void *MyMemcpy(void *dest, const void *src, size_t n);
void *MyMemmove(void *dest, const void *src, size_t n);
int MyAtoi(const char *str);
char *MyItoa(int num, char *buffer, int base);

void TestFunc(int condition, const char *message);

#endif
