#include <stdio.h>
#include <string.h>

void Red() 
{
    printf("\033[1;31m");
}

void Green()
{
    printf("\033[0;32m");
}

void Reset()
{
    printf("\033[0m");
}


int IsRotation(const char *s1, const char *s2)
{
    const char *runner1 = s1;
    const char *runner2 = s2;
    int is_rot = 0;
    int length = 0;
    /*
    while ('\0' != *runner1)
    {
        
        
        while (*runner1 != * runner2)
        {
            ++runner2;
        }
        
        length = strlen (runner2);
        is_rot = strncmp (runner1, runner2, length);
        runner2 = s2;
        ++runner1;
        
    }
    */
    
    return is_rot;  /* return 1 is success */
}

void TestFunc(int condition, const char *error)
{
    
    if (1 == condition)
    {   
        Green();
        printf("%s %s\n", "SUCCESS", error);
        Reset();
    }
    
    else
    {
        Red();
        printf("%s %s\n", "FAIL", error);
        Reset();
    } 
    
}




int main()
{
    
    int result = 0;
    
    const char str1[] = "121234";
    const char str2[] = "123412";
      
    TestFunc(IsRotation("abc", "def") == 1, "simple test");    
    TestFunc(IsRotation("", "") == 0, "empty string");
    TestFunc(IsRotation("abc", "") == 0, "one empty string");
    TestFunc(IsRotation("1111", "111111") == 1, "different length");
    
    return 0;
}












