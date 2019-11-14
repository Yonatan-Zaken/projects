/*********************************/
/*   			             	 */
/* Header file for work sheet 5  */
/*   Yonatan Zaken		         */
/*   Last Updated 13/11/19       */
/*   Reviewed by: Aviran         */   
/*			                   	 */
/*********************************/

#ifndef __LOOKUP_H__
#define __LOOKUP_H__

/* Eliminate unused parameter warning */
#define UNUSED(x) (void)(x)

#define NUM_ELEM 5    /* Size of LUT array                 */
#define INPUT_SIZE 50 /* Size of char array for user input */

typedef enum OP_STATUS {SUCCESS, FAIL_REMOVE, FAIL_COUNT, FAIL_APPEND, FAIL_PREPEND,  FAIL_CHRCMP, EXIT} OP_STATUS;

struct lut
    {
        char *name;
        int (*compare_ptr)(const char *, const char *);
        enum OP_STATUS (*op_ptr)(const char *, const char*);
    };


/**************************/
/* Function declerations  */
/**************************/

void Infrastructure(const char *file_name, struct lut lut_arr[]);
void InitFunc(struct lut lut_arr[]);
OP_STATUS ExitProg(const char *file_name, const char *str);
OP_STATUS RemoveFile(const char *file_name, const char *str);
OP_STATUS CountLines(const char *file_name, const char *str);
OP_STATUS Append(const char *file_name, const char *str);
OP_STATUS Preppend(const char *file_name, const char *str);
int AlwaysMatch(const char *str, const char *usr_input);
int StrCmp(const char *str, const char *usr_input);
int ChrCmp(const char *str, const char *usr_input);

#endif 





