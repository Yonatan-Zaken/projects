/*********************************/
/*   			             	 */
/*   Main file DS 1              */
/*   Yonatan Zaken		         */
/*   Last Updated 24/11/19       */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include "bitsarray.h"

#define BITS_IN_WORD 64

int main()
{
    char *buffer = (char*)calloc(BITS_IN_WORD, sizeof(char));
    size_t test1 = 18;
    size_t test2 = 1;
    size_t test3 = 5;
    size_t test4 = 15;
    size_t test5 = 10;    
    size_t test6 = 5;
    size_t test7 = 13;
    size_t test8 = 25;
     
    printf("Count of on bits in %ld is %ld\n", test1, BArrCountOn(test1));
    printf("Count of off bits in %ld is %ld\n", test2, BArrCountOff(test2));
    printf("Mirror of %ld is %lu\n", test3, BArrMirror(test3));
    printf("In BArrIsOn index %d is %d\n", 4, BArrIsOn(test4, 4));
    printf("In BArrIsOff index %d is %d\n", 4, BArrIsOff(test4, 4));
    printf("BArr set all bits returns %ld\n", BArrSetAllBits(test5));
    printf("BArr reset all bits returns %ld\n", BArrResetAllBits(test5));
    printf("Flipping index %d of %ld is %ld\n", 1, test6, BArrFlipBit(test6, 1));
    printf("SetOn index %d of %ld is %ld\n", 2, test7, BArrSetOn(test7, 2));
    printf("SetOff index %d of %ld is %ld\n", 3, test7, BArrSetOff(test7, 3));
    printf("%ld representation as string %s\n",test8 ,BArrToString(test8, buffer));
    
    free(buffer); buffer = NULL;
    
    return 0;
}
