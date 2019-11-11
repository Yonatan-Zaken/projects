/*********************************/
/*   			             	 */
/*				                 */
/*Implementing file work sheet 4 */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*			  	                 */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Function declarations */

void IfElse(void);
void SwitchCase(void);

int main()
{
     
    /* IfElse(); */
    
    SwitchCase();
    
    
    return 0;    
}


/* This function inplements the exercise via If Else declerations */

void IfElse(void)
{

    char c = 0;

    system("stty -icanon -echo");
    
    while(1 != c)
    {
        printf("\nPress A or T to print\nOr press esc to exit program:\n\n");
        c = getchar();
        
        if(65 == c)
        {
            printf("%c pressed\n", c);
        }
        
        else if(84 == c)
        {
            printf("%c pressed\n", c);
        }
        
        else if(27 == c)
        {
            printf("Exiting Program\n");
            return;        
        } 
        
        else
        {
            printf("Invalid Key\n");
            continue;
        } 
    }
    
    system("stty icanon echo");
}    

/* This function inplements the exercise via Switch Case declerations */

void SwitchCase(void)
{   
    char c = 0;
    
    system("stty -icanon -echo");
    
    while(1 != c)
    {
        printf("\nPress A or T to print\nOr press esc to exit program:\n\n");
        c = getchar();
       
        switch(c)
        {
            case 65:
                printf("%c pressed\n", c);
                break;
            
            case 84:
                printf("%c pressed\n", c);
                break;
            
            case 27:
                c = 1;
                printf("Exiting Program\n");
                break;
            
            default:
                printf("Invalid Key...\n");
                break;
        }
    }    
    
    system("stty icanon echo");  
}
















