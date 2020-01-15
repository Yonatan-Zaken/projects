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

#include "linkedlist.h"
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
    /*result = RecFib(50);*/
    end = clock();
    printf("RecFib: %f[sec]\n", (double)(end - begin) / CLOCKS_PER_SEC); 
    
    /*printf("rec fib: %lu\n\n", result);*/
    printf("iter fib: %lu\n\n", IterFib(2));  
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
    char dest[10] = "abcde";
    
    printf("strcat test:\n");
    
    printf("%s\n", RecStrcat(dest, src));
    printf("\n");

}
/*
static void StrstrTest()
{
    const char haystack[] = "abcdefghijk";
    const char needle[] = "defg";
    
    printf("haystack test:\n");
    
    printf("%s\n", RecStrstr(haystack, needle)); 
    printf("\n");
}
*/

static void FlipTest()
{
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5;
    node_t *head = NULL, *node1 = NULL, *node2 = NULL, *node3 = NULL, *node4 =NULL;
    
    printf("RecFlip test:\n");
    node1 = LLCreateNode(NULL, &x1);
    node2 = LLCreateNode(NULL, &x2);
    node3 = LLCreateNode(NULL, &x3);
    node4 = LLCreateNode(NULL, &x4);
    head = node1;
    
    RUN_TEST(0 == LLInsertAfter(node2, node1), "test");
    RUN_TEST(0 == LLInsertAfter(node3, node2), "test");
    RUN_TEST(0 == LLInsertAfter(node4, node3), "test");
    
    RUN_TEST(4 == LLSize(node1), "test");
    head = RecFlip(head);
    RUN_TEST(node4 == head, "test");
    LLDestroy(node4);    
    printf("\n");
}

int main()
{
    FibTest();
    StrlenTest();
    StrcmpTest();
    StrcpyTest();
    StrcatTest();
    /*StrstrTest();    */
    FlipTest();
    return 0;
}
