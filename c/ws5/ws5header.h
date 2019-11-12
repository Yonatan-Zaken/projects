/*********************************/
/*   			             	 */
/*				                 */
/* Header file for work sheet 5  */
/*   Yonatan Zaken		         */
/*   Last Updated 12/11/19       */
/*   Reviewed by:           */   
/*			                   	 */
/*			  	                 */
/*********************************/

#ifndef __LOOKUP_H__
#define __LOOKUP_H__

/* Function declerations */

int InitFunc();
enum OP_STATUS ExitProg(const char *str, FILE *fp);
enum OP_STATUS RemoveFile(const char *str, FILE *fp);
enum OP_STATUS CountLines(const char *str, FILE *fp);
int Compare(const char *str, const char *usr_input);
enum OP_STATUS AddToFile(const char *str, FILE *fp);

#endif 
