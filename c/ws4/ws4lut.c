/*********************************/
/*   			             	 */
/*				                 */
/*Implementing file work sheet 4 */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by: daniel         */   
/*			                   	 */
/*			  	                 */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ws4head.h"

/* This function sets all function pointers to empty function */

void LutInit(int (*lut_ptr[])(char), int n)
{
    int i = 0;
    
    for(i = 0; i < 256; i++)
    {
        lut_ptr[i] = &EmptyFunc;
    }
    
    lut_ptr[27] = &ExitProg;
    lut_ptr[65] = &PrintA;
    lut_ptr[84] = &PrintT;
    
    LutPrint(lut_ptr);
}


/* This function initializes 3 pointers to functions */
/* Each function performs a task according to input */
/* from keyboard */

void LutPrint(int (*lut_ptr[])(char))
{
    int return_value = 0;   
    char c = 0;
    
    system("stty -icanon -echo");
    
    while (1 != return_value)
    {
        printf("\nPress A or T to print\nOr press esc to exit program:\n");    
        c = getchar();
        return_value = (*lut_ptr[c]) (c);
    }
    
    system("stty icanon echo");
    
}

/* This function prints A if A is pressed */

int PrintA(char c)
{
    printf("%c pressed\n", c);
    return 0;
}

/* This function prints T if T is pressed */

int PrintT(char c)
{
    printf("%c pressed\n", c);
    return 0;
}

/* This function prints T if T is pressed */

int ExitProg(char c)
{
    return 1;
}

/* This is and empty function */

int EmptyFunc(char c)
{
   return 0;
}










