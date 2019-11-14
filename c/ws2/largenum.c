#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEC 96

char *AddLongNumbers(char str1[], char str2[]);
void RevStr(char* str);
int GetMax(char *str1, char *str2);

int main()
{
    char str1[] = "999999";
    char str2[] = "999993";
    char *result = NULL;
    /* char *sum = AddLongNumbers(str1, str2); */
    RevStr(str1);
    RevStr(str2);
    
    result = AddLongNumbers(str1, str2);
    
    printf("str1 + str2 = %s\n", result);
    
    free(result);
    result = NULL;
    
    return 0;
}


char *AddLongNumbers(char str1[], char str2[])
{
    char *runner1 = str1;
    char *runner2 = str2;
    
    int sum = 0;
    int carry = 0;
    int max_size = GetMax(str1, str2);
    
    char *result = (char*) malloc(max_size * sizeof(char) + 2);
    char *rewind = result;
    
    while ('\0' != *runner1 && '\0' != *runner2)
    {
        sum = (*runner1) + (*runner2) + carry - DEC;
        carry = (sum / 10);
        *result = (char)(sum % 10) + (DEC / 2);
        
        ++runner1;
        ++runner2;
        ++result;
    }
    
    if (*runner1 == *runner2)
    {
        sum = carry;
        *result = (char)(sum % 10) + (DEC / 2);
    }
    
    if ('\0' == *runner1 && '\0' != *runner2)
    {
        sum = (*runner2) + carry - (DEC / 2);
        *result = (char)(sum % 10) + (DEC / 2);
        ++runner2;
        ++result;
        strcpy(result, runner2);
    }
    
    else if ('\0' == *runner2 && '\0' != *runner1)
    {
        sum = (*runner1) + carry - (DEC / 2);
        *result = (char)(sum % 10) + (DEC / 2);
        ++runner1;
        ++result;
        strcpy(result, runner1);
    }
    
    RevStr(rewind);
       
    return rewind;   
}

int GetMax(char *str1, char *str2)
{
    int max = 0;
    int str1_length = strlen(str1); 
    int str2_length = strlen(str2);
    max = (str1_length > str2_length) ? str1_length : str2_length; 
    
    return max;
}

void RevStr(char *str)
{
    int size = strlen(str);
    int i = 0;
    int j = 0;
    char temp = 0;
    
    for(i = 0, j = size - 1; i < size / 2; i++, j--)
    {
        temp = *(str + i);
        *(str + i) = *(str + j);
        *(str + j) = temp;
    }   
}














