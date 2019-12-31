/*********************************/
/*   			             	 */
/*   Implementing file DS 1      */
/*   Yonatan Zaken		         */
/*   Last Updated 27/11/19       */
/*   Reviewed by: Shye           */   
/*			                   	 */
/*********************************/

#include <stddef.h>     /* use of size_t type */
#include <string.h>     /* strlen */
#include <assert.h>     /* assert check for null pointer */
#include "bitsarray.h"  /* bits array data structure functions */

#define MASK1 0x5555555555555555
#define MASK2 0xaaaaaaaaaaaaaaaa
#define MASK3 0x3333333333333333
#define MASK4 0xcccccccccccccccc
#define MASK5 0x0f0f0f0f0f0f0f0f
#define MASK6 0xf0f0f0f0f0f0f0f0
#define MASK7 0x00ff00ff00ff00ff
#define MASK8 0xff00ff00ff00ff00
#define MASK9 0x0000ffff0000ffff
#define MASK10 0xffff0000ffff0000
#define MASK11 0x00000000ffffffff
#define MASK12 0xffffffff00000000
#define MSB 0x8000000000000000
#define ONE_MASK 1UL

#define WORD_IN_BITS 64

#define ASCII_ZERO 48

/***********************************************************/
/* This function gets a size_t value and a position and    */
/* returns if the bit is on                                */   
/***********************************************************/

int BArrIsOn(size_t bits, int position)
{

    return ((bits >> (position - 1)) & ONE_MASK);
}

/***********************************************************/
/* This function gets a size_t value and a position and    */
/* returns if the bit is off                               */   
/***********************************************************/

int BArrIsOff(size_t bits, int position)
{
  
    bits = ~(bits);
    return ((bits >> (position - 1)) & ONE_MASK);
}

/***********************************************************/
/* This function gets a size_t value and roatates it to    */
/* the left num_of_rotations times                         */
/***********************************************************/

size_t BArrRotateLeft(bitsarr_t bits, int num_of_rotations)
{
    while (0 < (num_of_rotations % WORD_IN_BITS))
    {
        if (MSB == (bits & (ONE_MASK << (WORD_IN_BITS - 1))))
        {
            bits <<= 1;
            bits |= 1UL;
        }
        
        else
        {
            bits <<= 1;
        }
    
        --num_of_rotations;
    }

    return bits;
}

/***********************************************************/
/* This function gets a size_t value and roatates it to    */
/* the right num_of_rotations times                        */
/***********************************************************/

size_t BArrRotateRight(bitsarr_t bits, int num_of_rotations)
{
    while (0 < (num_of_rotations % WORD_IN_BITS))
    {
        if (1 == (bits & ONE_MASK))
        {
            bits >>= 1;
            bits |= (ONE_MASK << (WORD_IN_BITS - 1));
        }
        
        else
        {
            bits >>= 1;
        }
    
        --num_of_rotations;
    }
    
    return bits;
}

/***********************************************************/
/* This function return a size_t value with all bits set   */
/***********************************************************/

size_t BArrSetAllBits(bitsarr_t bits)
{
    bits ^= bits;
    return (~bits); 
}

/*************************************************************/
/* This function return a size_t value with all bits reset   */
/*************************************************************/

size_t BArrResetAllBits(bitsarr_t bits)
{
    bits ^= bits;
    return bits;
}

/************************************************************/
/* This function flips the state of the bit in the position */
/************************************************************/

size_t BArrFlipBit(bitsarr_t bits, int position)
{
    bits ^= (ONE_MASK << (position - 1));     
    return bits;
}

/***********************************************************/
/* This function sets the sets the bit indexed by position */
/* to be on and returns the new value                      */
/***********************************************************/

size_t BArrSetOn(bitsarr_t bits, int position)
{
    bits |= (ONE_MASK << (position - 1));        
    return bits;
}

/***********************************************************/
/* This function sets the sets the bit indexed by position */
/* to be off and returns the new value                     */
/***********************************************************/

size_t BArrSetOff(bitsarr_t bits, int position)
{
    
    bits &= ~(ONE_MASK << (position - 1));        
    return bits;
}

/*****************************************************************/
/* This functions sets the bit indexed by position to the state  */
/* mentioned by the variable status                              */
/*****************************************************************/

size_t BArrSetBit(bitsarr_t bits, int position, int status)
{
    size_t value_after_set = 0;
    
    if (1 == status)
    {
        value_after_set = BArrSetOn(bits, position);
    }
    
    else
    {
        value_after_set = BArrSetOff(bits, position);
    }
    
    return value_after_set;
}

/*************************************************************************/
/* This function gets a pointer to a size_t value and counts the number  */
/*  of bits that are set to 1 (on) using Hamming Weight method           */
/*************************************************************************/

size_t BArrCountOn(size_t bits)
{
    
    bits = (bits & MASK1) + ((bits >> 1) & MASK1);
    bits = (bits & MASK3) + ((bits >> 2) & MASK3);
    bits = (bits & MASK5) + ((bits >> 4) & MASK5);
    bits = (bits & MASK7) + ((bits >> 8) & MASK7);
    bits = (bits & MASK9) + ((bits >> 16) & MASK9);
    bits = (bits & MASK11) + ((bits >> 32) & MASK11);
    
    return bits;                              
}

/*************************************************************/
/* This function gets a pointer to a size_t value and counts */
/* the number of bits that are set to 0 (off)                */
/*************************************************************/

size_t BArrCountOff(size_t bits)
{
    
    bits = BArrCountOn(bits);
   
    return (WORD_IN_BITS - bits);
}

/***********************************************************/
/* This function gets a pointer to a size_t value and      */
/* converts it to string in a base 2 representation        */    
/***********************************************************/

char* BArrToString(size_t bits, char* buffer)
{
    size_t counter = 0;
    char *runner = buffer;
    
    assert (NULL != buffer);
    
    bits = BArrMirror(bits);
    
    while (WORD_IN_BITS > counter)
    {
        *runner = (((bits >> counter) & ONE_MASK) + ASCII_ZERO);
        ++runner;
        ++counter;
    }

    *runner = '\0';
    
    return buffer;
}

/************************************************************************/
/* This functions receives a pointer to a size_t value and mirrors the  */
/* bit representation of that value using Hamming Weight method         */
/************************************************************************/

size_t BArrMirror(bitsarr_t bits)
{
    
    bits = ((bits & MASK2) >> 1) | ((bits & MASK1) << 1);
    bits = ((bits & MASK4) >> 2) | ((bits & MASK3) << 2);
    bits = ((bits & MASK6) >> 4) | ((bits & MASK5) << 4);
    bits = ((bits & MASK8) >> 8) | ((bits & MASK7) << 8);              
    bits = ((bits & MASK10) >> 16) | ((bits & MASK9) << 16);
    bits = ((bits & MASK12) >> 32) | ((bits & MASK11) << 32);  
    
    return bits;
}

















