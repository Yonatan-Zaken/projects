/*********************************/
/*   			             	 */
/*Implementing file work sheet 6 */
/*   Yonatan Zaken		         */
/*   Last Updated 17/11/19       */
/*   Reviewed by: Ben Zaad       */   
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
    return x << y;      
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
/* This function gets a positive number and returns 1  */
/* that indicates if it's a power of 2. No loop        */
/*******************************************************/

int NPow2 (unsigned int n)
{
    int is_pow2 = 0;
    
    if (0 == n)
    {
        return is_pow2;
    }
    
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
    int bit_range = sizeof(unsigned int) * BYTE_SIZE;
    
    for (i = 0; i < arr_size; i++)
    {
        count = 0;
        j = bit_range;  
        temp = 1;
        
        while (0 < j)
        {
            
            if (temp & arr[i])  
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
            printf ("%d ", arr[i]);
        }   
    }
    printf("\n");
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
        if ((1 << i) & num)     
        {
            mirror = mirror | (1 << (BYTE_SIZE - 1 - i));
        }
    }
    
    return mirror;
}

/**************************************************************/
/* This function gets a value that is a size of a byte,       */
/* mirrors it without a loop using HAMMING WEIGHT method      */
/* returns the mirrored value.                                */
/**************************************************************/

unsigned int ByteMirror(unsigned int n)
{
	n = (((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1));
	n = (((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2));
	n = (((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4));
	n = (((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8));
	n = ((n >> 16) | (n << 16));
	
    return n;
}


/**************************************************************/
/* This function gets an unsigned char and returns 0 if       */
/* both its second and sixth bits are set                     */
/**************************************************************/

int CheckSetBitsOne(unsigned char n)
{
    unsigned char temp1 = 1;
    unsigned char temp2 = 1;
    int result = (((temp1 << 1) & n) >> 1) & (((temp2 << 5) & n) >> 5);
    
    return result;
}

/**************************************************************/
/* This function gets and unsigned char and returns "true"    */
/* if its second or sixth bits are set                        */
/**************************************************************/

int CheckSetBitsTwo(unsigned char n)
{
    unsigned char temp1 = 1;
    unsigned char temp2 = 1;
    unsigned int result = (((temp1 << 1) & n) >> 1) | (((temp2 << 5) & n) >> 5);
    
    return result; 
}

unsigned char SwapThreeFive(unsigned char n)
{
    unsigned char temp1 = 1U;
    unsigned char temp2 = 1U;
    unsigned char temp = 0U;
    unsigned char result = 0U;
    
    temp1 = (n >> 2) & temp1;
    temp2 = (n >> 4) & temp2;
    
    temp = temp1 ^ temp2;
    
    temp1 = temp << 2;
    temp2 = temp << 4;
    
    temp = temp1 | temp2;
    
    result = n ^ temp;
    
    return result; 
} 

/**************************************************************/
/* This function gets an unsigned int and returns the closest */
/* smaller number that is divisible by 16 without remainder   */
/**************************************************************/

unsigned int ClosestDivis(unsigned int n)
{
    unsigned int temp = ~15;  /* Zero in last 4 bits */    
    
    temp = n & temp;
    
    return temp;
}


/**************************************************************/
/* This function gets an unsigned int and returns the closest */
/* smaller number that is divisible by 16 without remainder   */
/**************************************************************/

void SwapVar(unsigned int *x,unsigned int *y)
{
    unsigned int *num1 = x;
    unsigned int *num2 = y;
    *num1 = (*num1) ^ (*num2);    
    *num2 = (*num2) ^ (*num1);
    *num1 = (*num1) ^ (*num2);  
}


/**********************************************/
/* This function gets an int and returns the  */ 
/* number of set bits using a loop            */
/**********************************************/

int CountSetLoop(unsigned int n)
{
    int count = 0;
    int i = 0;
    int bit_range = sizeof(unsigned int) * BYTE_SIZE; /* bit_range = 32 */
    
    for (i = 0; i < bit_range; i++)
    {
        if ((1 << i) & n)
        {
         ++count;
        }
    }
    
    return count;
}


/****************************************************/
/* This function gets an int and returns the number */ 
/*  of set bits using HAMMING WEIGHT                */
/****************************************************/

int CountSet(unsigned int n)
{
    unsigned int m1  = 0x55555555; 
    unsigned int m2  = 0x33333333; 
    unsigned int m4  = 0x0f0f0f0f; 
    unsigned int m8  = 0x00ff00ff; 
    unsigned int m16 = 0x0000ffff; 

    n = (n & m1 ) + ((n >>  1) & m1 ); 
    n = (n & m2 ) + ((n >>  2) & m2 );
    n = (n & m4 ) + ((n >>  4) & m4 ); 
    n = (n & m8 ) + ((n >>  8) & m8 );  
    n = (n & m16) + ((n >> 16) & m16);
    
    return n;
}

/***********************************************************************/
/* This function gets a float value and prints its bits representation */ 
/***********************************************************************/

void PrintFloatBits(float n)
{
    unsigned int *p;
    p = (unsigned int*)(&n); 
    
    PrintBinary(*p);
}

/*************************************************************************/
/* This function prints the number in gets as paramater in binary format */ 
/*************************************************************************/

void PrintBinary(unsigned int n)
{
    int size = sizeof(unsigned int) * BYTE_SIZE - 1; 
    int i = 0;
    
    for(i = 0; i <= size; i++)
    {
        n & (1 << (size - i)) ? printf("1") : printf("0");  
    }
}


















