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

#define NUM_ELEM 5

/* Function declerations */

struct lut
    {
        char *name;
        int (*compare_ptr)(const char *, const char *);
        enum OP_STATUS (*op_ptr)(const char *, const char*);
    };

void InitFunc(struct lut lut_arr[]);
enum OP_STATUS ExitProg(const char *file_name, const char *str);
enum OP_STATUS RemoveFile(const char *file_name, const char *str);
enum OP_STATUS CountLines(const char *file_name, const char *str);
enum OP_STATUS AddToTop(const char *file_name, const char *str);
enum OP_STATUS AddToBottom(const char *file_name, const char *str);
int AlwaysMatch(const char *str, const char *usr_input);
int Compare(const char *str, const char *usr_input);
void IterationFunc(const char *file_name, struct lut lut_arr[]);

#endif 
