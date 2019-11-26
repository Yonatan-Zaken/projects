/*********************************/
/*   			             	 */
/*   Implementing file DS 1      */
/*   Yonatan Zaken		         */
/*   Last Updated 24/11/19       */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include <string.h> /* strlen */
#include <assert.h> /* assert checks for null pointer */
#include "bitsarray.h"

#define WORD_IN_BYTES 8
#define WORD_IN_BITS 64
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

#define ONE_MASK 1UL

#define ASCII_ZERO 48

/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

int BArrIsOn(size_t bits, int position)
{
    size_t bit_num = bits;
    int is_on = 0;
    
    is_on = ((bit_num >> (position - 1)) & ONE_MASK);
    
    return is_on;
}

/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

int BArrIsOff(size_t bits, int position)
{
    size_t bit_num = ~(bits);
    int is_off = 0;
   
    is_off = ((bit_num >> (position - 1)) & ONE_MASK);
    
    return is_off;
}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrRotateLeft(size_t bits, int num_of_rotations)
{


}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrRotateRight(size_t bits, int num_of_rotations)
{

}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrSetAllBits(size_t bits)
{
    bits ^= bits;
    return (~bits); 
}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrResetAllBits(size_t bits)
{
    bits ^= bits;
    return bits;
}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrFlipBit(size_t bits, int position)
{
    bits ^= (ONE_MASK << (position - 1));     
    return bits;
}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrSetOn(size_t bits, int position)
{
    bits |= (ONE_MASK << (position - 1));        
    return bits;
}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrSetOff(size_t bits, int position)
{
    
    bits &= ~(ONE_MASK << (position - 1));        
    return bits;
}


/***********************************************************/
/*                                                         */
/*                                                         */
/***********************************************************/

size_t BArrSetBit(size_t bits, int position, int status)
{
    

}


/*************************************************************************/
/* This function gets a pointer to a size_t value and counts the number  */
/*  of bits that are set to 1 (on) using Hamming Weight method           */
/*************************************************************************/

size_t BArrCountOn(size_t bits)
{
    size_t bit_num = bits;
    
    bit_num = (bit_num & MASK1) + 
              ((bit_num >>  1) & MASK1);
    bit_num = (bit_num & MASK3) + 
              ((bit_num >>  2) & MASK3);
    bit_num = (bit_num & MASK5) + 
              ((bit_num >>  4) & MASK5);
    bit_num = (bit_num & MASK7) + 
              ((bit_num >>  8) & MASK7);
    bit_num = (bit_num & MASK9) + 
              ((bit_num >>  16) & MASK9);
    bit_num = (bit_num & MASK11) + 
              ((bit_num >>  32) & MASK11);
                                  
}


/*************************************************************/
/* This function gets a pointer to a size_t value and counts */
/* the number of bits that are set to 0 (off)                */
/*************************************************************/

size_t BArrCountOff(size_t bits)
{
    size_t bit_num = bits;
    
    bit_num = ~(bit_num);    
    
    bit_num = (bit_num & MASK1) + 
              ((bit_num >>  1) & MASK1);
    bit_num = (bit_num & MASK3) + 
              ((bit_num >>  2) & MASK3);
    bit_num = (bit_num & MASK5) + 
              ((bit_num >>  4) & MASK5);
    bit_num = (bit_num & MASK7) + 
              ((bit_num >>  8) & MASK7);
    bit_num = (bit_num & MASK9) + 
              ((bit_num >>  16) & MASK9);
    bit_num = (bit_num & MASK11) + 
              ((bit_num >>  32) & MASK11);
    
    return bit_num;
}

/***********************************************/
/*                                             */
/*                                             */
/***********************************************/

static void ReverseStr(char *source)
{
    int size = strlen(source);
    int stop_cond = size / 2;
    char *start = source;
    char *end = source + (size - 1); 
    char temp = 0;
    int i = 0;
    
    assert(NULL != source);
    
    for (i = 0; i < stop_cond; ++i)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }   
}

/***********************************************************/
/* This function gets a pointer to a size_t value and      */
/* converts it to string in a base 2 representation        */    
/***********************************************************/

char* BArrToString(size_t bits, char* buffer)
{
    size_t remainder = 0;
    size_t base = 2;
    size_t counter = BITS_IN_WORD;
    char *runner = buffer;
    
    assert (NULL != buffer);
    
    while (0 < counter)
    {
        remainder = bits % base;
        *runner = (remainder + ASCII_ZERO);
        bits /= base;
        --counter;
        ++runner;
    }

    *runner = '\0';
    
    ReverseStr(buffer);
    
    return buffer;
}


/************************************************************************/
/* This functions receives a pointer to a size_t value and mirrors the  */
/* bit representation of that value using Hamming Weight method         */
/************************************************************************/

size_t BArrMirror(size_t bits)
{
    size_t bit_num = bits;
    
    bit_num = ((bit_num & MASK2) >> 1) | 
              ((bit_num & MASK1) << 1);
    bit_num = ((bit_num & MASK4) >> 2) |
              ((bit_num & MASK3) << 2);
    bit_num = ((bit_num & MASK6) >> 4) |
              ((bit_num & MASK5) << 4);
    bit_num = ((bit_num & MASK8) >> 8) |
              ((bit_num & MASK7) << 8);              
    bit_num = ((bit_num & MASK10) >> 16) |
              ((bit_num & MASK9) << 16);
    bit_num = ((bit_num & MASK12) >> 32) |
              ((bit_num & MASK11) << 32);  
    
    return bit_num;
}

















