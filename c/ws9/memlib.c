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
    unsigned long constant_c = c;
    
    if (strlen(str) < n)
    {
        return NULL;
    }
    
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c; 
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c;
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c;
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c;
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c;
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c;
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c;
    constant_c = (constant_c << WORD_IN_BYTES) | constant_c;
    
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
        *(long*)runner = constant_c;
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
/* This function gets a pointer to a string str and sets its  */
/* first n bytes in memory to the the constant c              */
/**************************************************************/

void *MyMemcpy(void *dest, const void *src, size_t n)
{



}
































