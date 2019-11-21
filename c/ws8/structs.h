/*********************************/
/*   			             	 */
/*   Header file work sheet 8    */
/*   Yonatan Zaken		         */
/*   Last Updated 20/11/19       */
/*   Reviewed by: Yoav Hattav    */   
/*			                   	 */
/*********************************/


#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#define UNUSED(x) (void)(x)

#include <stdio.h>  /* use of printf */
#include <stdlib.h> /* use of malloc, realloc and free */ 
#include <string.h> /* use of strlen and strcat */
#include <assert.h>

#define ADD_INT_VAL 10
#define NUM_ELEMENTS 3
#define BUFFER_SIZE 20

typedef struct types_and_ops{
    void *data_type;
    void (*print_ptr)(const void *data_ptr);
    int (*add_ptr)(void *data_ptr);
    int (*clean_ptr)(void *data_ptr);

}types_and_oper;

int Initialize(types_and_oper inf_arr[]);
int Infrastructure(types_and_oper inf_arr[]);
void PrintInt(const void *data_ptr);
void PrintFloat(const void *data_ptr);
void PrintStr(const void *data_ptr);
int AddToInt(void *data_ptr);
int AddToFloat(void *data_ptr);
int AddToStr(void *data_ptr);
int CleanMem(void *data_ptr);
int EmptyFunc(void *data_ptr);

#endif





