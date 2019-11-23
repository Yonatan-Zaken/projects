/*********************************/
/*   			             	 */
/*   Main file work sheet 9      */
/*   Yonatan Zaken		         */
/*   Last Updated 21/11/19       */
/*   Reviewed by: Yoav Hattav    */   
/*			                   	 */
/*********************************/

#include "memlib.h"

int main()
{
    /* Test for MyMemset */
    void *result = NULL;
    char str1[30] = "helloworldhelloworld";    
    char str2[] = "abcde";
    char *str3 = str2 + 2;
    char str4[] = "44432324";
    int num = -59;   
    char str5[11] = {0};
    int check_endianess = 1;  
    
    /*Test fir MyMemset */
    TestFunc(strcmp(MyMemset(str1, 'c', 18), 
                      memset(str1, 'c', 18)) == 0, "MyMemset test");
    
    /* Test for MyMemcpy */
    TestFunc(strcmp(MyMemcpy(str3, str2, 3), 
                      memcpy(str3, str2, 3)) == 0, "MyMemcpy test");
    
    /*Test for MyAtoi */
    TestFunc(MyAtoi(str4) == atoi(str4), "Test Myatoi vs atoi");
    
    /* Test for MyItoa */
    printf("%s\n", MyItoa(num, str5, 10));   
    
    /* Test is little Endian */
    IsLittleEndian(check_endianess);
    
    /*
    if (NULL == result)
    {
        printf("n bytes exceed buffer size. aborting...\n");
        return 1;
    }
    
    printf("%s\n", (unsigned char*)result);*/
    
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










