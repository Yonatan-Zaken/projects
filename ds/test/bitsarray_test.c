/*********************************/
/*   			             	 */
/*   Main file DS 1              */
/*   Yonatan Zaken		         */
/*   Last Updated 27/11/19       */
/*   Reviewed by: Shye           */   
/*			                   	 */
/*********************************/

#include <stdio.h>      /* print */
#include <stdlib.h>     /* calloc */
#include <string.h>     /* strcmp */
#include "bitsarray.h"  /* bits array data structure functions */

#define BITS_IN_WORD 64
#define MSB 0x8000000000000000
#define MASKMIRR1 0x00ff00ff00ff00ff
#define MASKMIRR2 0xff00ff00ff00ff00
#define MASKROTATE1 0x00000000ffffffff
#define MASKROTATE2 0xffffffff00000000
#define STRING_CMP1 "0000000000000000000000000000000000000000000000000000000000011001"
#define STRING_CMP2 "0000000000000000000000000000000000000000000000000000010001000001"

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
                                  if (test)\
                                  {\
                                     printf(GREEN);\
                                     printf("SUCCESS\n");\
                                     printf(NORMAL);\
                                  }\
                                  else\
                                  {\
                                     printf(RED);\
                                     printf("FAIL %s\n", error_message);\
                                     printf(NORMAL);\
                                  }\
                                  }


static void TestBArrCountOn()
{
    printf("Test BArrCountOn\n");
    RUN_TEST((2 == BArrCountOn(18)), "BArrCountOn Test");
    RUN_TEST((64 == BArrCountOn(~0UL)), "BArrCountOn Test");
    printf("\n");
}

static void TestBArrCountOff()
{
    printf("Test BArrCountOff\n");
    RUN_TEST((63 == BArrCountOff(1)), "BArrCountOff Test");
    RUN_TEST((0 == BArrCountOff(~0)), "BArrCountOff Test");
    printf("\n");
}

static void TestBArrMirror()
{
    printf("Test BArrMirror\n");
    RUN_TEST((MSB == BArrMirror(1UL)), "BArrMirror Test");
    RUN_TEST((1UL == BArrMirror(MSB)), "BArrMirror Test");
    RUN_TEST(MASKMIRR1 == BArrMirror(MASKMIRR2), "BArrMirror Test");
    RUN_TEST(~0UL == BArrMirror(~0UL), "BArrMirror Test"); 
    printf("\n");   
}

static void TestBArrIsOn()
{
    printf("Test BArrIsOn\n");
    RUN_TEST(1 == BArrIsOn(15, 4), "BArrIsOn Test");
    RUN_TEST(1 == BArrIsOn(MSB, 64), "BArrIsOn Test");
    printf("\n");
}

static void TestBArrIsOff()
{
    printf("Test BArrIsOff\n");
    RUN_TEST(1 == BArrIsOff(5, 2), "BArrIsOff Test");
    RUN_TEST(0 == BArrIsOff(MSB, 64), "BArrIsOff Test");
    printf("\n");
}

static void TestBArrSetAllBits()
{
    printf("Test BArrSetAllBits\n");
    RUN_TEST(~0UL == BArrSetAllBits(12), "BArrSetAllBits Test");
    RUN_TEST(~0UL == BArrSetAllBits(0), "BArrSetAllBits Test");
    printf("\n");
}

static void TestBArrResetAllBits()
{
    printf("Test BArrResetAllBits\n");
    RUN_TEST(0UL == BArrResetAllBits(321), "BArrResetAllBits Test");
    RUN_TEST(0UL == BArrResetAllBits(~0), "BArrResetAllBits Test");
    printf("\n");
}

static void TestBArrFlipBit()
{
    printf("Test BArrFlipBit\n");
    RUN_TEST(4UL == BArrFlipBit(5UL, 1), "BArrFlipBit Test");
    RUN_TEST(0UL == BArrFlipBit((MSB), 64), "BArrFlipBit Test");
    printf("\n");
}

static void TestBArrSetOn()
{
    printf("Test BArrSetOn\n");
    RUN_TEST(15UL == BArrSetOn(13UL, 2), "BArrSetOn Test");
    RUN_TEST(MSB == BArrSetOn(0UL, 64), "BArrSetOn Test");
    printf("\n");
}

static void TestBArrSetOff()
{
    printf("Test BArrSetOff\n");
    RUN_TEST(36 == BArrSetOff(100UL, 7), "BArrSetOff Test");
    RUN_TEST(64 == BArrSetOff(64UL, 1), "BArrSetOff Test");
    printf("\n");
}

static void TestBArrToString()
{
    char *buffer = (char*)calloc(BITS_IN_WORD + 1, sizeof(char));
    
    printf("Test BArrToString\n");
    RUN_TEST(0 == strcmp(STRING_CMP1, BArrToString(25, buffer)),
                                          "BArrToString Test");
    RUN_TEST(0 == strcmp(STRING_CMP2, BArrToString(1089, buffer)), 
                                          "BArrToString Test");
            
    printf("\n");
    
    free(buffer); buffer = NULL;
}

static void TestBArrSetBit()
{
    printf("Test BArrSetBit\n");
    RUN_TEST(41 == BArrSetBit(57UL, 5, 0), "BArrSetBit Test");
    RUN_TEST(MSB == BArrSetBit(0UL, 64, 1), "BArrSetBit Test");
    printf("\n");
}

static void TestBArrRotateLeft()
{
    printf("Test BArrRotateLeft\n");
    RUN_TEST(4 == BArrRotateLeft(MSB, 3), "BArrRotateLeft Test");
    RUN_TEST(MSB == BArrRotateLeft(1UL, 63), "BArrRotateLeft Test");
    printf("\n");
}

static void TestBArrRotateRight()
{
    printf("Test BArrRotateRight\n");
    RUN_TEST(MASKROTATE1 == BArrRotateRight(MASKROTATE2, 32), 
                                     "BArrRotateRight Test");
    RUN_TEST(MSB == BArrRotateRight(8UL, 4), "BArrRotateRight Test");
    printf("\n");
}

int main()
{
    
    TestBArrCountOn();
    TestBArrCountOff();
    TestBArrMirror();
    TestBArrIsOn();
    TestBArrIsOff();
    TestBArrSetAllBits();
    TestBArrResetAllBits();
    TestBArrFlipBit();
    TestBArrSetOn();
    TestBArrSetOff();
    TestBArrToString();
    TestBArrSetBit();
    TestBArrRotateLeft();
    TestBArrRotateRight();
    
    return 0;
}
