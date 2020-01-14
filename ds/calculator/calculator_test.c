/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Caclculator                 */
/*   Author: Yonatan Zaken       */
/*   Last Updated 12/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */
#include <assert.h>
#include <math.h>

#include "calculator.h"

#define UNUSED(x) (void)(x)

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

static void CalcTest1()
{
    char str[] = "2 + 5";
    char str2[] = "2 - 5";
    char str3[] = "2 + 5 + 5 + 8 - 15";
    char str4[] = "2";
    char str5[] = "24+";
    char str6[] = ".6 + 4";
    char str7[] = "+";
    double result = 0;
    printf ("Addition Subtraction Test\n");
    
    RUN_TEST(0 == Calculator(str, &result), "calculator1");
    RUN_TEST(7 == result, "result1");
    
    RUN_TEST(0 == Calculator(str2, &result), "calculator1");
    RUN_TEST(-3 == result, "result1");
    
    RUN_TEST(0 == Calculator(str3, &result), "calculator1");
    RUN_TEST(5 == result, "result1");

    RUN_TEST(0 == Calculator(str4, &result), "calculator1");
    RUN_TEST(2 == result, "result1");
    
    RUN_TEST(0 == Calculator(str4, &result), "calculator1");
    RUN_TEST(2 == result, "result1");
    
    RUN_TEST(1 == Calculator(str5, &result), "calculator1");
    
    RUN_TEST(0 == Calculator(str6, &result), "calculator1");
    RUN_TEST((double)4.6 == result, "result1");        
    
    RUN_TEST(1 == Calculator(str7, &result), "calculator1");
    
    printf("\n\n");
}

static void CalcTest2()
{
    char str[] = "2 * 5";
    char str2[] = "2 / 5";
    char str3[] = "2 * 2 / 8";
    char str4[] = "**2";
    char str5[] = ".3 * 8";
    char str6[] = "2^3^2";
    char str7[] = "0.5^2.5";
    double result = 0;
    
    printf ("Multiply, division and power Test\n");
    
    RUN_TEST(0 == Calculator(str, &result), "calculator1");
    RUN_TEST(10 == result, "result1");
    
    RUN_TEST(0 == Calculator(str2, &result), "calculator1");
    RUN_TEST(0.4 == result, "result1");
    
    RUN_TEST(0 == Calculator(str3, &result), "calculator1");
    RUN_TEST(0.5 == result, "result1");
    
    RUN_TEST(1 == Calculator(str4, &result), "calculator1");
    
    RUN_TEST(0 == Calculator(str5, &result), "calculator1");
    RUN_TEST(2.4 == result, "result1");
    
    RUN_TEST(0 == Calculator(str6, &result), "calculator1");
    RUN_TEST(512 == result, "result1");
    
    RUN_TEST(0 == Calculator(str7, &result), "calculator1");
    RUN_TEST(pow(0.5,2.5) == result, "result1");
    

    printf("\n\n");
}

static void CalcTest3()
{
    char str[] = "3 * 2 - 4";
    char str2[] = "3 / 2 * 3 / 4 + 5";
    char str3[] = "3/2 + 5 * 2.5 - 2 ^ 3 ^ 2 ";
    char str4[] = "2^^2";
    char str5[] = "2^3+5";
    double result = 0;
    
    printf ("Mult, div, add, sub and pow Test\n");
    
    RUN_TEST(0 == Calculator(str, &result), "calculator1");
    RUN_TEST(2 == result, "result1");
    
    RUN_TEST(0 == Calculator(str2, &result), "calculator1");
    RUN_TEST(6.125 == result, "result1");
    
    RUN_TEST(0 == Calculator(str3, &result), "calculator1");
    RUN_TEST(-498 == result, "result1");
    
    RUN_TEST(1 == Calculator(str4, &result), "calculator1");
    
    RUN_TEST(0 == Calculator(str5, &result), "calculator1");
    printf("%f\n", result);
    RUN_TEST(13 == result, "result1");
    
    printf("\n\n");
    
}

static void CalcTest4()
{
    char str[] = "(3 + 2)";
    char str2[] = "2 + 3 - (5 - 2)";
    char str3[] = "(5 + 2)^2^2";
    char str4[] = "0.2 * ((5 + 3) * 4)";
    char str5[] = "(((3 + 2)";
    double result = 0;
    
    printf ("Parentheses Test\n");
    
    RUN_TEST(0 == Calculator(str, &result), "calculator1");
    RUN_TEST(5 == result, "result1");
    
    RUN_TEST(0 == Calculator(str2, &result), "calculator1");
    RUN_TEST(2 == result, "result1");
    
    RUN_TEST(0 == Calculator(str3, &result), "calculator1");
    RUN_TEST(2401 == result, "result1");
    
    RUN_TEST(0 == Calculator(str4, &result), "calculator1");
    RUN_TEST(6.4 == result, "result1");
    
    RUN_TEST(0 == Calculator(str5, &result), "calculator1");
    RUN_TEST(5 == result, "result1");
    
    printf("\n\n");
}

int main()
{
    CalcTest1(); 
    CalcTest2();
    CalcTest3();
    CalcTest4();
    
    return 0;
}
