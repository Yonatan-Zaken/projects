/*********************************/
/*   			             	 */
/*				                 */
/* Header file for work sheet 3  */
/*   Yonatan Zaken		         */
/*   Last Updated 4/11/19        */
/*   Reviewed by: Ben            */   
/*			                   	 */
/*			  	                 */
/*********************************/

#ifndef __ENVIRONMENTVAR_H__
#define __ENVIRONMENTVAR_H__

char **CopyEnv(const char**, int);
void PrintEnv(const char** );
void StringToLower(char* );
int BufferSize(const char ** );
char *StrDup(const char * );
void CleanEnvCopy(char** );

#endif 
