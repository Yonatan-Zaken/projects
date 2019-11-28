/*********************************/
/*   			             	 */
/*   Header file DS 1            */
/*   Yonatan Zaken		         */
/*   Last Updated 27/11/19       */
/*   Reviewed by: Shye           */   
/*			                   	 */
/*********************************/

#ifndef __BITS_ARRAY_H__ 
#define __BITS_ARRAY_H__

#include <stddef.h> /* size_t type */

typedef size_t bitsarr_t;

/* This function sets all bits to 1 */
size_t BArrSetAllBits(bitsarr_t bits);

/* This function sets all bits to 0 */
size_t BArrResetAllBits(bitsarr_t bits);

/* This function checks if given bit is 1 */
int BArrIsOn(bitsarr_t bits, int position);

/* This function checks if given bit is 0 */
int BArrIsOff(bitsarr_t bits, int position);

/* This function return the number of the on bits using Hamming Weight */
size_t BArrCountOn(size_t bits);

/* This function return the number of the off bits */
size_t BArrCountOff(size_t bits);

/* This function sets specific bit to the given status */
size_t BArrSetBit(bitsarr_t bits, int position, int status);

/* This function sets specific bit to 1 */
size_t BArrSetOn(bitsarr_t bits, int position);

/* This function sets specific bit to 0 */
size_t BArrSetOff(bitsarr_t bits, int position);

/* This function rotate the array to left n times */
size_t BArrRotateLeft(bitsarr_t bits, int num_of_rotations);

/* This function rotate the array to right n times */
size_t BArrRotateRight(bitsarr_t bits, int num_of_rotations);

/* This function return a string presentation of given bits array */
char* BArrToString(bitsarr_t bits, char* buffer);

/* This function flips specific bit */
size_t BArrFlipBit(bitsarr_t bits, int position);

/* This function mirroring a given bits array */
size_t BArrMirror(bitsarr_t bits);

#endif







