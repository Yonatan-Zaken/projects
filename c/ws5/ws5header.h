/*********************************/
/*   			             	 */
/*				                 */
/* Header file for work sheet 5  */
/*   Yonatan Zaken		         */
/*   Last Updated 12/11/19       */
<<<<<<< HEAD
/*   Reviewed by: Aviran         */   
=======
/*   Reviewed by:           */   
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557
/*			                   	 */
/*			  	                 */
/*********************************/

#ifndef __LOOKUP_H__
#define __LOOKUP_H__

<<<<<<< HEAD
/* Eliminate unused parameter warning */
#define UNUSED(x) (void)(x)

#define NUM_ELEM 5    /* Size of LUT array                 */
#define INPUT_SIZE 50 /* size of char array for user input */


struct lut
    {
        char *name;
        int (*compare_ptr)(const char *, const char *);
        enum OP_STATUS (*op_ptr)(const char *, const char*);
    };


/**************************/
/* Function declerations  */
/**************************/

void InitFunc(struct lut lut_arr[]);
enum OP_STATUS ExitProg(const char *file_name, const char *str);
enum OP_STATUS RemoveFile(const char *file_name, const char *str);
enum OP_STATUS CountLines(const char *file_name, const char *str);
enum OP_STATUS Append(const char *file_name, const char *str);
enum OP_STATUS Preppend(const char *file_name, const char *str);
int AlwaysMatch(const char *str, const char *usr_input);
int StrCmp(const char *str, const char *usr_input);
void Infrastructure(const char *file_name, struct lut lut_arr[]);
int ChrCmp(const char *str, const char *usr_input);
=======
/* Function declerations */

int InitFunc();
enum OP_STATUS ExitProg(const char *str, FILE *fp);
enum OP_STATUS RemoveFile(const char *str, FILE *fp);
enum OP_STATUS CountLines(const char *str, FILE *fp);
enum OP_STATUS AddToFile(const char *str, FILE *fp);
int Compare(const char *str, const char *usr_input);
void IterationFunc(const char *file_name);
>>>>>>> 57ec6b8436f47b88b5abc8a6198cd9ff44c23557

#endif 
