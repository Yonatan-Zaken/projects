/*********************************/
/*   			             	 */
/*Implementing file work sheet 8 */
/*   Yonatan Zaken		         */
/*   Last Updated 20/11/19       */
/*   Reviewed by: Yoav Hattav    */   
/*			                   	 */
/*********************************/

#include "structs.h"

/******************************************************/
/* This function initializes the array of structures  */
/******************************************************/

int Initialize(types_and_oper inf_arr[])
{
    *((int*)(&inf_arr[0].data_type)) = 77; 
    inf_arr[0].print_ptr = &PrintInt; 
    inf_arr[0].add_ptr = &AddToInt;
    inf_arr[0].clean_ptr = &EmptyFunc;
    
    *((float*)(&inf_arr[1].data_type)) = 10.24; 
    inf_arr[1].print_ptr = &PrintFloat;
    inf_arr[1].add_ptr = &AddToFloat;
    inf_arr[1].clean_ptr = &EmptyFunc;
    
    inf_arr[2].data_type = malloc(sizeof(char) * 6);
    if (NULL == inf_arr[2].data_type)
    {
        return 1;
    }
    
    strcpy(inf_arr[2].data_type, "hello");
    
    inf_arr[2].print_ptr = &PrintStr;
    inf_arr[2].add_ptr = &AddToStr;
    inf_arr[2].clean_ptr = &CleanMem;
    
    return 0;
}


/********************************************************************/
/* This function iterates through the array of structures and for   */
/* each element: prints it, adds a int value to it and prints       */
/* it again with the new value                                      */
/********************************************************************/

int Infrastructure(types_and_oper inf_arr[])
{
    int i = 0;
    int status = 0;
    
    for(i = 0; i < NUM_ELEMENTS; i++)
    {
        inf_arr[i].print_ptr(inf_arr[i].data_type);
        
        status = inf_arr[i].add_ptr(&inf_arr[i].data_type);
        if (1 == status)
        {
            printf("Fail to re-allocate memory, aborting...");
            return 1;
        }
        inf_arr[i].print_ptr(inf_arr[i].data_type);
        inf_arr[i].clean_ptr(inf_arr[i].data_type);  
    }
    
    return 0;
}

/**************************************************/
/* This function gets a void pointer and prints   */
/* the address it is pointing to                  */
/**************************************************/

void PrintInt(const void *data_ptr)
{
    assert(NULL != data_ptr);     
    
    printf("%d\n", *((int*)(&data_ptr)));
}

/*************************************************/
/* This function gets a void pointer and prints  */
/* the address it is pointing to                 */
/*************************************************/

void PrintFloat(const void *data_ptr)
{
    assert(NULL != data_ptr);

    printf("%f\n", *((float*)(&data_ptr)));
}

/*************************************************/
/* This function gets a void pointer and prints  */
/* the string it is pointing to in memory        */
/*************************************************/

void PrintStr(const void *data_ptr)
{
    assert(NULL != data_ptr);    
    
    printf("%s\n", (char*)data_ptr);
}

/*******************************************************************/
/* This function gets a void pointer to a pointer and adds a       */
/* int value to the address it is pointing to                      */
/*******************************************************************/

int AddToInt(void *data_ptr)
{
    assert(NULL != data_ptr);    
    
    *((int*)data_ptr) = *((int*)(data_ptr)) + ADD_INT_VAL;        
    
    return 0;
}

/*******************************************************************/
/* This function gets a void pointer to a pointer and adds a       */
/* int value to the address it is pointing to                      */
/*******************************************************************/

int AddToFloat(void *data_ptr)
{
    assert(NULL != data_ptr);

    *((float*)data_ptr) = *((float*)(data_ptr)) + ADD_INT_VAL; 
    
    return 0;
}

/*********************************************************************/
/* This function gets a void pointer to a pointer to a string        */
/* and concatenates a value to that string                           */
/*********************************************************************/

int AddToStr(void *data_ptr)
{
    int num = ADD_INT_VAL;
    int counter = 0;
    int str_length = strlen(*(char**)data_ptr);
    char buffer[BUFFER_SIZE];
 
    assert(NULL != data_ptr);   
       
    while (0 != num)
    {
        num /= 10;
        ++counter;     
    }
    
    *((char**)data_ptr) = realloc(*((char**)data_ptr), str_length + counter + 1);
    if (NULL == *((char**)data_ptr))
    {
        return 1;
    }
       
    sprintf(buffer, "%d", ADD_INT_VAL);
    strcat(*(char**)data_ptr, buffer);
    
    return 0;
}


/*************************************************************/
/* This function gets a void pointer and frees the address   */
/* memory that has been allocated to it                      */
/*************************************************************/

int CleanMem(void *data_ptr)
{
    assert(NULL != data_ptr);
    
    free(data_ptr);
    data_ptr = NULL;
    
    return 0;
}

/*************************************************/
/* This a an empty function which is pointed to  */
/* by pointers to functions that are not in use  */
/*************************************************/

int EmptyFunc(void *data_ptr)
{
    UNUSED(data_ptr);
    return 0;
}










