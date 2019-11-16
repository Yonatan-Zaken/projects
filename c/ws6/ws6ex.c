/*********************************/
/*   			             	 */
/*Implementing file work sheet 6 */
/*   Yonatan Zaken		         */
/*   Last Updated 14/11/19       */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include "ws6.h"

/***************************************/
/* This function returns the result of */
/* the computation x AND (2 XOR y)     */
/***************************************/

long Pow2 (unsigned int x, unsigned int y)
{
    return (x & (2 ^ y));      
}

/********************************************************/
/* This function gets a positive number and returns 1   */
/* if it's a power of 2. Using loop                     */
/********************************************************/

int NPow2Loop (unsigned int n)
{
    int is_pow2 = 1;    
    
    if (0 == n)
    {
        is_pow2 = 0;
        return is_pow2;
    }
    
    while (1 ^ n)
    {
        if (1 & n)
        {
            is_pow2 = 0;
        }
        
        n = n >> 1;
    }
      
    return is_pow2;
}

/*******************************************************/
/* This function gets a positive number and returns a  */
/* value that indicates if it's a power of 2. No loop  */
/*******************************************************/

int NPow2 (unsigned int n)
{
    int is_pow2 = 0;
    
    if (0 == (n & (n - 1)))
    {
        is_pow2 = 1;
    }    
    
    return is_pow2;
}

int AddOne(int n)
{
    int y = 1;
    int num = n;
    
    /* If rightmost bit is 1, adding 1 will lead to a carry on 1 */
    while (y & num)       
    {
        num = num ^ y;
        y = y << 1;     /* Shift y to add 1 to the next bit on the left */
    }
    
    /* If the right most bit is 0, XOR is equivalent to adding 1 */
    num = num ^ y;      
  
    return num;
}

/**********************************************************/
/* This function gets and array and its size and counts   */
/* the number of set bits each element has. If an element */
/* has exactly 3 bits set the function prints it.         */
/**********************************************************/

void ThreeBitsOn(unsigned int arr[], int arr_size)
{
    int i = 0;
    int j = 0;
    int count = 0;
    int temp = 0;
    
    for (i = 0; i < arr_size; i++)
    {
        count = 0;
        j = BIT_RANGE;  /* BIT_RANGE = 32 */
        temp = 1;
        
        while (0 < j)
        {
            
            if (temp & arr[i])  /* Indicates if a bit is set or not */
            {
                ++count;
            }
            
            temp <<= 1;        
            
            if (THREE_SET < count)
            {
                break;
            }
            
            --j;
        }
        
        if (THREE_SET == count)
        {
            printf ("%d\n", arr[i]);
        }   
    }
}

/********************************************************/
/* This function gets a value that is a size of a byte, */
/* mirrors it via loop and returns the mirrored value.  */
/********************************************************/

unsigned char ByteMirrorLoop(unsigned char num)
{
    char mirror = 0;
    int i = 0;
    
    for (i = 0; i < BYTE_SIZE; i++)
    {
        if ((1 << i) & num)     /* Check if bit at current index is set */
        {
            /* Set the bit of the mirror index to i */
            mirror = mirror | (1 << (BYTE_SIZE - 2 - i));
        }
    }
    
    return mirror;
}

/**************************************************************/
/* This function gets a value that is a size of a byte,       */
/* mirrors it without a loop and returns the mirrored value.  */
/**************************************************************/




/**************************************************************/
/* This function gets an unsigned char and returns 0 if       */
/* both its second and sixth bits are set                     */
/**************************************************************/

int CheckSetBitsOne(unsigned char n)
{
    unsigned char temp = 1;
    int result = 0;
    
    temp <<= 1;
    temp &= n;
    
    temp <<= 4;
    temp &= n;
    
    temp >>= 5;
    
    switch (temp)
    {
        case 1:
            break;
            
        case 0:
            result = 1;
            break; 
    }
    
    return result;
}

/**************************************************************/
/* This function gets and unsigned char and returns "true"    */
/* if its second or sixth bits are set                        */
/**************************************************************/

int CheckSetBitsTwo(unsigned char n)
{
    int result = 0;
    unsigned char temp1 = 1;
    unsigned char temp2 = 1;
    unsigned char test = 0;
    
    temp1 <<= 1;
    temp1 &= n;
    
    temp2 <<= 4;
    temp2 &= n;
    
    test = temp1 + temp2;
    
    switch (test)
    {
        case 0:
            result = 1;
            break;
    }
    
    return result;
    
}

unsigned char SwapThreeFive(unsigned char n)
{
    
    
    
}

/**************************************************************/
/* This function gets an unsigned int and returns the closest */
/* smaller number that is divisible by 16 without remainder   */
/**************************************************************/
/*
unsigned int ClosestDivis(unsigned int n)
{
    if (16 > n)
    {
        printf("Invalid input.\n");
        return 0;
    }
    
    
    
}
*/
/**********************************************/
/* This function gets an int and returns the  */ 
/* number of set bits using a loop            */
/**********************************************/

int CountSetLoop(int n)
{
    int count = 0;
    int i = 0;
    
    for (i = 0; i < BIT_RANGE; i++)
    {
        if ((1 << i) & n)
        {
         ++count;
        }
    }
    
    return count;
}


/**********************************************/
/* This function gets an int and returns the  */ 
/* number of set bits without using a loop    */
/**********************************************/

int CountSet(int n)
{


}



















