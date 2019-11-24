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
    char str1[30] = "helloworldhelloworld";    
    char str2[] = "abcde";
    char *str3 = str2 + 2;
    char str4[] = "44432324";
    char str5[11] = {0};  
    char str6[] = "abcdefghijklmno";
    char *str7 = str6 + 5;
    char str8[] = "abcd";
    char str9[] = "anec";
    char str10[] = "tenv";
    
    int base = 10;
    int num = 2;   
    int endianness = 1;
    
    /*Test fir MyMemset */
    TestFunc(0 == strcmp(MyMemset(str1, 'c', 18), 
                         memset(str1, 'c', 18)), "MyMemset test");
    
    /* Test for MyMemcpy */
    TestFunc(0 == strcmp(MyMemcpy(str3, str2, 3), 
                         memcpy(str3, str2, 3)), "MyMemcpy test");
    
    /* Test for MyMemmove */
    TestFunc(0 == strcmp(MyMemmove(str7, str6, 8), 
                           memmove(str7, str6, 8)), "MyMemmove test");

    /*Test for MyAtoi */
    TestFunc(MyAtoi(str4) == atoi(str4), "Test Myatoi vs atoi");
    
    /* Test for MyItoa */
    printf("%s\n", MyItoa(num, str5, base));   
    
    /* Test IsLittleEndian Function */
    IsLittleEndian();
    
    /* Test IS_LITTLE_ENDIAN MACRO */
    IS_LITTLE_ENDIAN(endianness);
    
    /* Test CheckThreeArrays */
    CheckThreeArrays(str8, str9, str10, 4, 4, 4);
    
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










