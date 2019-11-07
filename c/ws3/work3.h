/*********************************/
/*   			             	 */
/*				                 */
/* Header file for work sheet 3  */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by:		         */   
/*			                   	 */
/*			  	                 */
/*********************************/

#ifndef __POINTER_H__
#define __POINTER_H__

void StringToLower(char* );
void PrintEnv(const char** );
char **CopyEnv(const char** );
void CleanEnvCopy(char** );
void MyAlloc(char* );
int BufferSize(const char **);
char *StrDup(const char *);

#endif 
