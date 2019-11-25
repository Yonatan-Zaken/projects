/*********************************/
/*   			             	 */
/*Implementing file work sheet 9 */
/*   Yonatan Zaken		         */
/*   Last Updated 24/11/19       */
/*   Reviewed by: Eliya          */   
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
    
    assert(NULL != str);
    
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
    if (0 != ((size_t)runner % WORD_IN_BYTES) && (0 < n))
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
        *(size_t*)runner = const_word;
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
    
    assert(NULL != dest);
    assert(NULL != src);
    
    if (0 != ((size_t)runner_dest % WORD_IN_BYTES) && (0 < n))
    {
        *runner_dest = *runner_src;
        ++runner_dest;
        ++runner_src;
        --n;
    }
    
    while (1 <= (n / WORD_IN_BYTES))
    {
        *(size_t*)runner_dest = *(size_t*)runner_src;
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
    unsigned char *runner_dest = dest;
    const unsigned char *runner_src = src;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    if ((((size_t)runner_src + n > (size_t)runner_dest)) 
                          && (runner_dest > runner_src))
    {
        runner_dest = runner_dest + (n - 1);    
        runner_src = runner_src + (n - 1);
    
        while (0 < n)
        {
            *runner_dest = *runner_src;
            --runner_dest;
            --runner_src; 
            --n;   
        }
        
        return dest;
    }
    
    else 
    {
        runner_dest = MyMemcpy(dest, src, n);
    }
    
    return runner_dest;
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
    
    assert(NULL != source);
    
    for (i = 0; i < stop_cond; ++i)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }   
}


/********************************************************************/
/* This function gets a pointer to a string and returns the number  */
/* represented in the string as an int value                        */
/********************************************************************/

int MyAtoi(const char *str, int base)
{
    const char *runner = str;
    int result = 0;
    int sign = 1;
    
    assert(NULL != str);
    
    if ('-' == *runner)
    {
        sign = -1;
        ++runner;
    }
    
    /*ReverseStr((char*)runner);*/
    
    while ('\0' != *runner)
    {
        if ('A' <= *runner)
        {
            result = result * base + ((*runner) - ASCII_CHAR);
        }
        
        else
        {
            result = result * base + ((*runner) - ASCII_ZERO);
        }
        
        ++runner;
    }    
    
    return (result * sign);
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
    
    assert(NULL != buffer);
        
    if (0 > num)
    {
        num = -num;
        is_negative = 1;
    }
    
    if (0 == num)
    {
        *runner = ASCII_ZERO;
        *(runner + 1) = '\0';
        return runner;
    }
    
    while (0 != num)
    {
        remainder = num % base;
        
        if (9 < remainder)
        {
            *runner = (remainder + ASCII_CHAR);
            num /= base;
            ++runner;
        }
            
        else
        {
            *runner = (remainder + ASCII_ZERO);
            num /= base;
            ++runner;
        }
    }
    
    if (1 == is_negative)
    {
        *runner = '-';
        ++runner;
    }
    
    *runner = '\0';
    
    ReverseStr(buffer);
    
    return buffer;        
}

/*****************************************************/
/* This function prints the endianness of the system */
/*****************************************************/

void IsLittleEndian(void)
{
    int num = 1;
    int *p = &num; 
    
    if (1 == *(char*)p)
    {
        printf("Endianness is Little Endian.\n");
    }
    
    else printf("Endianness is Big Endian.\n");
}


/*****************************************************************/
/* This function checks which characters occur in s1 and s2 but  */
/* not in the string s3                                          */   
/*****************************************************************/

int CheckThreeArrays(char array1[], char array2[], char array3[], int size1, int size2, int size3)
{
	int i = 0;
	unsigned char value = 0;

	int **arr = (int **)calloc(2 ,sizeof(int *));
	if (NULL == arr)
	{
	    printf("no memory allocated CheckThreeArrays function\n");
	    return 1;
	}
	 
    	for (i = 0; i < 2; ++i)
	{
         	arr[i] = (int *)calloc(127 ,sizeof(int));
         	if (NULL == arr[i])
         	{
         	    printf("no memory allocated CheckThreeArrays function.\n");
         	    return 1;
         	} 
	}

	i = 0;
	
	while (i < size1)
	{
		value = array1[i];
		if (0 == arr[0][(int)value])
		{
		    ++arr[0][(int)value];
		}
		++i;
	}
	
	i = 0;

 	while (i < size2)
	{
		value = array2[i];
		if (1 == arr[0][(int)value])
		{
			++arr[0][(int)value];
		}
		++i;
	}
	
	i = 0;

	while (i < size3)
	{
		value = array3[i];
	    ++arr[1][(int)value];
		++i;
	}
	
	printf("Check Three Arrays Result: ");
	
	for (i = 0; i < 127; ++i)
	{
		if ((arr[0][i] == 2) && (arr[1][i] == 0))
		{
			printf("%c ",(char)i);
		}
	}
	
	printf("\n");
    
	free(arr[0]);
	free(arr[1]);
	free(arr);
    arr = NULL;
	
	return 0;
}

                            















