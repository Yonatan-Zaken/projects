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
    
    TestFunc(NPow2Loop(1) == 1, "NPow2Loop test with 1");
    TestFunc(NPow2Loop(433) == 0, "NPow2Loop test with 433");
    TestFunc(NPow2Loop(512) == 1, "NPow2Loop test with 512");
  
    /* NPow2 test with no loop*/ 
    
    TestFunc(NPow2(1) == 1, "NPow2 test with 1");
    TestFunc(NPow2(7) == 0, "NPow2 test with 7");
    TestFunc(NPow2(1048576) == 1, "NPow2 test with 1048576");
    
    
    /* AddOne test */
    TestFunc(AddOne(2147483647) == (2147483647 + 1), "AddOne to 2147483647");
    TestFunc(AddOne(-300) == (-300 + 1), "AddOne to -300");
    TestFunc(AddOne(-2147483648) == (-2147483648 + 1), "AddOne to -2147483648");
    
    /* ThreeBitsOn test */    
    
    ThreeBitsOn(arr1, 9);
    
    
    /* ByteMirror test */
    /*
    
    printf("The mirror of %c is %c\n", 'a', ByteMirrorLoop('a'));
    */
    
    /* CheckSetBitsOne test */
    /*
    printf("%s\n", (CheckSetBitsOne('z') == 1) ? "Both set", "Not both set")
    */
    
    /* CheckSetBitsTwo test */
    /*
    printf("%s\n", (CheckSetBitsOne('z') == 1) ? "One Set", "None set")
    */
    
    /* SwapThreeFive test */
    /*
    printf("Swap bits 3 and 5 of %d = %d\n", 16, SwapThreeFive(16)); 
    */
    
    /* Swap variables test */
    /*
    SwapVar(&x, &y);
    printf("%d %d", x, y);
    */
    
    /* ClosestDivis test */
    /*
    printf("%u closest divisible by 16 is = %u\n", 33, ClosestDivis(33));
    printf("%u closest divisible by 16 is = %u\n", 17, ClosestDivis(17));
    */
    
    /* CountSet test */
    /*
    printf("Number of bits set is %d\n", CountSet(312));
    printf("Number of bits set is %d\n", CountSet(7));
    */
    
    /* PrintFloatBits test */
    /*
    PrintFloatBits(-2.25);
    PrintFloatBits(-300);
    */
    
    
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

























