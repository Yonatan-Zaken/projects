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

/* Function declerations */

void LutInit(int (*lut_ptr[])(char), int n);
void LutPrint(int (*lut_ptr[])(char));
int PrintA(char c);
int PrintT(char c);
int ExitProg(char c);
int EmptyFunc(char c);


int main()
{
    int (*lut_ptr[256])(char);
    
    system("stty -icanon -echo");   
    
    LutInit(lut_ptr, 256);
    LutPrint(lut_ptr);      
    
    system("stty icanon echo");
    
    return 0;    
}


/* This function sets all function pointers to empty function */

void LutInit(int (*lut_ptr[])(char), int n)
{
    int i = 0;
    
    for(i = 0; i < n; i++)
    {
        lut_ptr[i] = &EmptyFunc;
    }
}


/* This function initializes 3 pointers to functions */
/* Each function performs a task according to input */
/* from keyboard */

void LutPrint(int (*lut_ptr[])(char))
{   
    char c = 0;
    int return_value = 0;
    
    lut_ptr[27] = &ExitProg;
    lut_ptr[65] = &PrintA;
    lut_ptr[84] = &PrintT;
    
    while (27 != return_value)
    {
        printf("\nPress A or T to print\nOr press esc to exit program:\n");    
        c = getchar();
        return_value = (*lut_ptr[c]) (c);
    }
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
    return 27;
}

/* This is and empty function */

int EmptyFunc(char c)
{
   return 0;
}










