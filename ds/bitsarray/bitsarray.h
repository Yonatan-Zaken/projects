/*********************************/
/*   			             	 */
/*   Header file DS 1            */
/*   Yonatan Zaken		         */
/*   Last Updated 26/11/19       */
/*   Reviewed by: Shye           */   
/*			                   	 */
/*********************************/

#ifndef __BITS_ARRAY_H__ 
#define __BITS_ARRAY_H__

#include <stddef.h> /* size_t type */

typedef size_t bitsarr_t;

/* This function sets all bits to 1 */
size_t BArrSetAllBits(size_t bits);

/* This function sets all bits to 0 */
size_t BArrResetAllBits(size_t bits);

/* This function checks if given bit is 1 */
int BArrIsOn(size_t bits, int position);

/* This function checks if given bit is 0 */
int BArrIsOff(size_t bits, int position);

/* This function return the number of the on bits using Hamming Weight */
size_t BArrCountOn(size_t bits);

/* This function return the number of the off bits */
size_t BArrCountOff(size_t bits);

/* This function sets specific bit to the given status */
size_t BArrSetBit(size_t bits, int position, int status);

/* This function sets specific bit to 1 */
size_t BArrSetOn(size_t bits, int position);

/* This function sets specific bit to 0 */
size_t BArrSetOff(size_t bits, int position);

/* This function rotate the array to left n times */
size_t BArrRotateLeft(size_t bits, int num_of_rotations);

/* This function rotate the array to right n times */
size_t BArrRotateRight(size_t bits, int num_of_rotations);

/* This function return a string presentation of given bits array */
char* BArrToString(size_t bits, char* buffer);

/* This function flips specific bit */
size_t BArrFlipBit(size_t bits, int position);

/* This function mirroring a given bits array */
size_t BArrMirror(size_t bits);

#endif







