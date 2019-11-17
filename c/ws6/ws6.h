/*********************************/
/*   			             	 */
/*   Header file work sheet 6    */
/*   Yonatan Zaken		         */
/*   Last Updated 14/11/19       */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/


#ifndef __BITWISE_H__
#define __BITWISE_H__

#define THREE_SET 3
#define BYTE_SIZE 8

long Pow2(unsigned int x, unsigned int y);
int NPow2Loop (unsigned int n);
int NPow2 (unsigned int n);
int AddOne(int n);
void ThreeBitsOn(unsigned int arr[], int arr_size);
unsigned char ByteMirrorLoop(unsigned char);

int CheckSetBitsOne(unsigned char n);
int CheckSetBitsTwo(unsigned char n);
unsigned char SwapThreeFive(unsigned char n);
unsigned int ClosestDivis(unsigned int n);

int CountSetLoop(unsigned int n);
int CountSet(unsigned int n);
void SwapVar(unsigned int *x, unsigned int *y);
void PrintFloatBits(float n); 
void PrintBinary(unsigned int);

#endif
