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
/* This function gets a positive number and returns a   */
/* value that indicates if it's a power of 2 via loop   */
/********************************************************/

int NPow2Loop (unsigned int n)
{
    int is_pow2 = 1;    
    
    if (0 == n)
    {
        is_pow2 = 0;
        return 1;
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












