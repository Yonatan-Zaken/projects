/*********************************/
/*   			             	 */
/*   Main file work sheet 9      */
/*   Yonatan Zaken		         */
/*   Last Updated 24/11/19       */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*********************************/

#include "memlib.h"

int main()
{
    char *str1  = (char*)malloc(sizeof(char) * 40);
    char *str2  = (char*)malloc(sizeof(char) * 40);   
    char *str3  = (char*)malloc(sizeof(char) * 40);
    char *str4  = (char*)malloc(sizeof(char) * 40);
    char *str5  = (char*)malloc(sizeof(char) * 40); 
    char *str6  = (char*)malloc(sizeof(char) * 40);
    char *str7  = NULL;
    char *str8  = (char*)malloc(sizeof(char) * 40);
    char *str9  = (char*)malloc(sizeof(char) * 40);
    char *str10 = (char*)malloc(sizeof(char) * 40);
    
    char str11[] = "abcd";
    char str12[] = "anec";
    char str13[] = "tenv";
    
    int base = 10;
    int num = 2493;   
    int endianness = 1;
    
    strcpy(str1, "helloworldhelloworld");
    strcpy(str2, "abcdefghijklmnopqrstuvw");
    strcpy(str3, "xxxxxxxxxxxxxxx");
    strcpy(str4, "2243");
    strcpy(str5, "\0\0\0\0\0\0\0\0\0\0\0");
    strcpy(str6, "abcdefghijklmnopqrstuvwxyz");
    str7 = str6 + 5;
    strcpy(str8, "QQQQQQQQQQQQQQQQQQQQQQQQQ");
    strcpy(str9, "AAAAAAAAAAAAAAAAA");
    strcpy(str10, "A20");
    
    /*Test fir MyMemset */
    TestFunc(0 == strcmp(MyMemset(str1, 'c', 18), 
                         memset(str1, 'c', 18)), "MyMemset test");
    
    /* Test for MyMemcpy */
    TestFunc(0 == strcmp(MyMemcpy(str3, str2, 3), 
                         memcpy(str3, str2, 3)), "MyMemcpy test");
    
    /* Test for MyMemmove With Overlap */
    TestFunc(0 == strcmp(MyMemmove(str7, str6, 8), 
                           memmove(str7, str6, 8)), "MyMemmove Overlap test");
     
    /* Test for MyMemmove Without Overlap */
    TestFunc(0 == strcmp(MyMemmove(str9, str8, 16), 
                           memmove(str9, str8, 16)), "MyMemmove test");
    
    /* Test for MyAtoi for any base */
    printf("%d\n", MyAtoi(str10, 11));
    
    /*Test for MyAtoi in base 10 vs atoi function*/
    TestFunc(MyAtoi(str4, 10) == atoi(str4), "MyAtoi test");
    
    /* Test for MyItoa */
    printf("%s\n", MyItoa(num, str5, base));   
    
    /* Test IsLittleEndian Function */
    IsLittleEndian();
    
    /* Test IS_LITTLE_ENDIAN MACRO */
    IS_LITTLE_ENDIAN(endianness);
    
    /* Test CheckThreeArrays */
    CheckThreeArrays(str11, str12, str13, 4, 4, 4);
    
    free(str1); str1 = NULL;
    free(str2); str2 = NULL;
    free(str3); str3 = NULL;
    free(str4); str4 = NULL;
    free(str5); str5 = NULL;
    free(str6); str6 = NULL;
    free(str8); str8 = NULL;
    free(str9); str9 = NULL;
    free(str10); str10 = NULL;
    
    return 0;
}

/*****************************/
/* This a a testing function */
/*****************************/

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










