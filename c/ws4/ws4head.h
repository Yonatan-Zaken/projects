/*********************************/
/*   			             	 */
/*				                 */
/* Header file for work sheet 4  */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*			  	                 */
/*********************************/

#ifndef __LOOKUP_H__
#define __LOOKUP_H__

/* Function declerations */

void LutInit(int (*lut_ptr[])(char), int n);
void LutPrint(int (*lut_ptr[])(char));
int PrintA(char c);
int PrintT(char c);
int ExitProg(char c);
int EmptyFunc(char c);

#endif 
