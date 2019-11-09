#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *AddLongNumbers(char str1[], char str2[]);
char *RevStr(char* );
int GetMin(char *str1, char *str2);
int GetMax(char *str1, char *str2);

int main()
{
    char str1[] = "23";
    char str2[] = "19";
   
    char *sum = AddLongNumbers(str1, str2);
    
    return 0;
}


char *AddLongNumbers(char str1[], char str2[])
{
    int sum = 0;
    int min = GetMin(str1, str2);
    int str_size = GetMax(str1, str2);
    char *str1_rev = RevStr(str1);
    char *str2_rev = RevStr(str2);
    
    char *result = (char*) malloc(str_size * sizeof(char));
    
    for(; 0 < min; --min)
    {
        sum = (*(str1 + i)) + (*(str2 + i)) 
    }
    
    
    
      
    return result;   
}

int GetMax(char *str1, char *str2)
{
    int max = 0;
    int str1_length = strlen(str1); 
    int str2_length = strlen(str2);
    max = (str1_length > str2_length) ? str1_length + 2 : str2_length + 2; 
    
    return max;
}

int GetMin(char *str1, char *str2)
{
    int min = 0;
    int str1_length = strlen(str1); 
    int str2_length = strlen(str2);
    min = (str1_length > str2_length) ? str2_length + 2 : str1_length + 2; 
    
    return min;
}


char *RevStr(char *str)
{
    int size = strlen(str);
    int i = 0;
    int j = 0;
    int temp = 0;
    
    for(i = 0, j = size - 1; i < size / 2; i++, j--)
    {
        temp = *(str + i);
        *(str + i) = *(str + j);
        *(str + j) = temp;
    }
    
    return str;
    
}














