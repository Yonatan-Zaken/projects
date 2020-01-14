/*********************************/
/*   			             	 */
/*   Recursion                   */
/*   Author: Yonatan Zaken       */
/*   Last Updated 14/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/
#include <stdio.h> /* printf */
#include <time.h>  /* clock */
#include <string.h> /*strlen */

#include "recursion.h"

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

static void FibTest()
{
    size_t result = 0;
    clock_t begin = 0, end = 0;
    printf("FibRec Test:\n");
    begin = clock();
    result = RecFib(50);
    end = clock();
    printf("RecFib: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC); 
    
    printf("%lu\n\n", result);  
}

static void StrlenTest()
{
    char str[] = "fibfib##";
    printf("strlen test:\n");
    
    RUN_TEST(strlen(str) == RecStrlen(str), "strlen test");
    printf("\n");
}

static void StrcmpTest()
{
    int result = 0;
    char str1[] = "abc";
    char str2[] = "abc";
    
    char str3[] = "abc";
    char str4[] = "abg";
    printf("strcmp test:\n");
    
    result = RecStrcmp(str1, str2);
    RUN_TEST(strcmp(str1, str2) == RecStrcmp(str1, str2), "strcmp test");
    printf("%d\n", result);
    
    result = RecStrcmp(str3, str4);
    RUN_TEST(strcmp(str3, str4) == RecStrcmp(str3, str4), "strcmp test");
    printf("%d\n", result);
    printf("%d\n", strcmp(str3, str4));
    printf("\n");
    
}

static void StrcpyTest()
{
    char src[] = "$$";
    char dest[] = "abcde";
    printf("strcpy test:\n");
    
    printf("%s\n", RecStrcpy(dest, src));
    RUN_TEST(0 == strcmp(src, dest), "strcpy test");
    printf("%lu %lu\n", strlen(src), strlen(dest));
    printf("%s\n", src);
    printf("%s\n", dest);
    printf("\n");
}

static void StrcatTest()
{
    char src[] = "$$";
    char dest[] = "abcde";
    
    printf("strcat test:\n");

}

int main()
{
    /*FibTest();*/
    StrlenTest();
    StrcmpTest();
    StrcpyTest();
    StrcatTest();
    
    return 0;
}
