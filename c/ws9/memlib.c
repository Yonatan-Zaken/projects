/*********************************/
/*   			             	 */
/*Implementing file work sheet 9 */
/*   Yonatan Zaken		         */
/*   Last Updated 21/11/19       */
/*   Reviewed by: Yoav Hattav    */   
/*			                   	 */
/*********************************/

#include "memlib.h"

/**************************************************************/
/* This function gets a pointer to a string str and sets its  */
/* first n bytes in memory to the the constant c              */
/**************************************************************/

void *MyMemset(void *str, int c, size_t n)
{
    unsigned char *runner = str;
    size_t const_word = c;
    int i = 0;
    
    if (strlen(str) < n)
    {
        return NULL;
    }
    
    /* Create a word sized constant from c */
    for (i = 0; i < WORD_IN_BYTES - 1; ++i)
    {
        const_word = (const_word << WORD_IN_BYTES) | const_word; 
    }
    
    /* If address is not aligned */
    if (0 != ((size_t)runner % WORD_IN_BYTES))
    {   
        while (0 != ((size_t)runner % WORD_IN_BYTES))
        {
            *runner = c;
            ++runner;
            --n;
        }
    }
    
    while (1 <= (n / WORD_IN_BYTES))
    {
        *(long*)runner = const_word;
        runner = runner + WORD_IN_BYTES;
        n -= WORD_IN_BYTES;
    }
    
    while (0 != n)
    {
        *runner = c;
        ++runner;
        --n;
    }
    
    return str; 
}

/**************************************************************/
/* This function gets pointers to strings src and dest and    */
/* copies the first n bytes pointed by src to dest            */
/**************************************************************/

void *MyMemcpy(void *dest, const void *src, size_t n)
{
    unsigned char *runner_dest = dest;
    const unsigned char *runner_src = src;
    
    while (1 <= (n / WORD_IN_BYTES))
    {
        *(long*)runner_dest = *(long*)runner_src;
        runner_dest += WORD_IN_BYTES;
        runner_src += WORD_IN_BYTES;
        n -= WORD_IN_BYTES;
    }
    
    while (0 != n)
    {
        *runner_dest = *runner_src;
        ++runner_dest;
        ++runner_src;
        --n;
    }
    
    return dest;
}

/**************************************************************/
/* This function gets pointers to strings src and dest and    */
/* copies the first n bytes pointed by src to dest            */
/**************************************************************/

void *MyMemmove(void *dest, const void *src, size_t n)
{
    

}

/********************************************************************/
/* This function gets a pointer to a string and returns the number  */
/* represented in the string as an int value                        */
/********************************************************************/

int MyAtoi(const char *str)
{
    const char *runner = str;
    int result = 0;
    int sign = 1;
    
    if ('-' == *runner)
    {
        sign = -1;
        ++runner;
    }
    
    while (('\0' != *runner) && ('.' != *runner))
    {
        result = result * 10 + ((*runner) - 48);
        ++runner;
    }    
    
    return (result * sign);
}

/*************************************************************/
/* Service function for MyItoa. This function gets a pointer */
/* to a string and reverses it.                              */
/*************************************************************/

static void ReverseStr(char *source)
{
    int size = strlen(source);
    int stop_cond = size / 2;
    char *start = source;
    char *end = source + (size - 1); 
    char temp = 0;
    int i = 0;
    
    for (i = 0; i < stop_cond; ++i)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }    
}

/*********************************************************************/
/* This function gets an int value and returns a pointer to a string */
/* representing that int value                                       */
/*********************************************************************/

char *MyItoa(int num, char *buffer, int base)
{
    char *runner = buffer;
    int is_negative = 0;
    int remainder = 0;    
    
    if (0 > num)
    {
        num = -num;
        is_negative = 1;
    }
    
    while (0 != num)
    {
        remainder = num % base;
        
        if (9 < remainder)
        {
            *runner = (remainder + 55);
            num /= base;
            ++runner;
        }
            
        else
        {
            *runner = (remainder + 48);
            num /= base;
            ++runner;
        }
    }
    
    if (1 == is_negative)
    {
        *runner = '-';
    }
    
    ReverseStr(buffer);
    
    return buffer;        
}

/*****************************************************/
/* This function prints the endianness of the system */
/*****************************************************/

void IsLittleEndian(int num)
{
    int *p = &num; /* num = 1 */
    
    if (1 == *(char*)p)
    {
        printf("Endianness order is Little Endian.\n");
    }
    
    else printf("Endianness order is Big Endian\n");
}





















