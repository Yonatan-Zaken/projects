/*********************************/
/*   			             	 */
/*   Main file work sheet 6      */
/*   Yonatan Zaken		         */
/*   Last Updated 14/11/19       */
/*   Reviewed by:          */   
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
    /*
    printf("%d\n", NPow2Loop(0));
    printf("%d\n", NPow2Loop(1));
    printf("%d\n", NPow2Loop(433));
    printf("%d\n", NPow2Loop(512)); 
    */
    
    /* NPow2 test with no loop*/ 
    /*
    printf("%s\n", (NPow2(0) == 1) ? "is power of 2" : "isn't power of 2");
    printf("%s\n", (NPow2(1) == 1) ? "is power of 2" : "isn't power of 2");
    printf("%s\n", (NPow2(7) == 1) ? "is power of 2" : "isn't power of 2");
    printf("%s\n", (NPow2(1048576) == 1) ? "is power of 2" : "isn't power of 2");
    */
    
    /* AddOne test */
    /*
    printf("Add 1 to 2147483647 = %d\n", AddOne(2147483647));
    printf("Add 1 to 100 = %d\n", AddOne(100));
    printf("Add 1 to -1 = %d\n", AddOne(-1));
    printf("Add 1 to -2147483648 = %d\n", AddOne(-2147483648));
    */
    
    
    /* ThreeBitsOn test */    
    /*
    ThreeBitsOn(arr1, 9);
    */
    
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
    */
    
    /* PrintFloatBits test */
    /*
    PrintFloatBits(-2.25);
    PrintFloatBits(-300);
    */
    
    
    return 0;
}





























