#include <stdio.h>
#include <string.h>
#include <ctype.h>


int IsPalindrome(char *str)
{
   int isPal = 1;
   int str_size = strlen(str) - 1;
   char *runner1 = str;
   char *runner2 = str + str_size;
   
   if (*runner1 != *runner2)
   {
        isPal = 0;
   }
   
   else
   {
        ++runner1;
        --runner2;
   }
   
   return isPal;
   
}

void PrintSeven(int from, int to)
{
    
    int is_seven = 0;
    int i = 0;
    for (i = from; i <= to; i++)
    {
        int temp = i;
        is_seven = 0;
        if (0 == (temp % 7))
        {
            printf("BOOM\n");
            continue;
        } 
        
        while (1 < temp)
        {
            if (0 == ((temp % 10) % 7))
            {
                is_seven = 1;
                break;
            } 
            
            temp = temp / 10;
        } 
        
        if (is_seven)
        {
            printf("BOOM\n");
            continue;
        }
        
        else
        {
            printf("%d\n", i);  
        }
    }
}

void Swap(int *ptr1, int *ptr2)
{
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void RmSpaces(char *s)
{
    char *runner1 = s;
    char *runner2 = s;
    char *temp = s;
    
    while (isspace(*runner1))
    {
        ++runner1;
    }
    
    strcpy(runner2, runner1);
    printf("%s\n", runner2);
    
    runner1 = runner2;
    temp = runner2;
    
    while ('\0' != *runner1)
    {
        if(isspace(*runner1) && isspace(*(runner1 + 1)))
        {
            while (isspace(*runner1))
            {
                ++runner1;
            }
            
            strcpy(++runner2, runner1);
            runner1 = runner2;
        }    
        
        ++runner1;
        ++runner2;
    }
    
    printf("%s\n", temp);
      
}

int main()
{
    char str[] = "   \thello  world   two";
    
    RmSpaces(str);
    
    return 0;
}









