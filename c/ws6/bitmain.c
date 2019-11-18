/*********************************/
/*   			             	 */
/*   Main file work sheet 6      */
/*   Yonatan Zaken		         */
/*   Last Updated 17/11/19       */
/*   Reviewed by: Ben Zaad       */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include "ws6.h"

int main()
{
    unsigned int x = 4;        
    unsigned int y = 5;
    
    /* Array for testing ThreeBitsOn function */
    unsigned int arr1[] = {7, 1, 2, 7, 11, 13, 19, 21, 140};
    
    /* Pow2 test */    
    /*printf("Pow2(x, y) = %ld\n\n", Pow2(x, y));*/
    
    /* NPow2 test */ 
    
    TestFunc(NPow2Loop(0) == 0, "NPow2Loop test with 1");
    TestFunc(NPow2Loop(433) == 0, "NPow2Loop test with 433");
    TestFunc(NPow2Loop(512) == 1, "NPow2Loop test with 512");
  
    /* NPow2 test with no loop*/ 
    
    TestFunc(NPow2(0) == 0, "NPow2 test with 1");
    TestFunc(NPow2(7) == 0, "NPow2 test with 7");
    TestFunc(NPow2(1048576) == 1, "NPow2 test with 1048576");
    
    /* AddOne test */
    TestFunc(AddOne(2147483647) == (2147483647 + 1), "AddOne to 2147483647");
    TestFunc(AddOne(-300) == (-300 + 1), "AddOne to -300");
    TestFunc(AddOne(-2147483648) == (-2147483648 + 1), "AddOne to -2147483648");
    
    /* ThreeBitsOn test */    
    
    ThreeBitsOn(arr1, 9);
   
    /* ByteMirror test */
    
    TestFunc(ByteMirrorLoop(140) == 49, "ByteMirror test /w loop");
    TestFunc(ByteMirrorLoop(103) == 230, "ByteMirror test /w loop");
    TestFunc(ByteMirror(140) == 822083584, "ByteMirror test no loop");
    TestFunc(ByteMirror(1) == 2147483648, "ByteMirror test no loop");
    
    /* CheckSetBitsOne test */
    TestFunc(CheckSetBitsOne(38) == 1, "CheckSetBitsOne test with 38");
    
    /* CheckSetBitsTwo test */
    
    TestFunc(CheckSetBitsTwo(32) == 1, "CheckSetBitsTwo test with 32");
    
    /* SwapThreeFive test */
    TestFunc(SwapThreeFive(16) == 4, "SwapThreeFive test with 16");
    
    /* Swap variables test */
    
    SwapVar(&x, &y);
    printf("x after swap = %d, y after swap = %d\n", x, y);
    
    /* ClosestDivis test */
    
    TestFunc(ClosestDivis(33) == 32, "ClosestDivis test with 33");
    TestFunc(ClosestDivis(100) == 96, "ClosestDivis test with 100");
    
    /* CountSet test */
    TestFunc(CountSetLoop(312) == 4, "CountSetLoop with 312");
    TestFunc(CountSetLoop(4294967295) == 32, "CountSetLoop with 4294967295");
    TestFunc(CountSet(312) == 4, "CountSet test with 312");
    TestFunc(CountSet(4294967295) == 32, "CountSet test with 4294967295");
     
    /* PrintFloatBits test */
    
    PrintFloatBits(-2.25);
    PrintFloatBits(-300);
    
    return 0;
}


void TestFunc(int condition, const char *message)
{
    
    if (1 == condition)
    {   
        printf("\033[0;32m");
        printf("%s %s\n", "SUCCESS", message);
    }
    
    else
    {
        printf("\033[1;31m");
        printf("%s %s\n", "FAIL", message);
    }
    
    printf("\033[0m"); 
}

























