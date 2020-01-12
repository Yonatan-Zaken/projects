#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__
           
typedef enum Status{
    SUCCESS,
    SYNTAX_ERROR,
    MEMORY_FAIL
} calc_status_t;

/*
    Gets an expression as string to calculate and a pointer to the result
    Return value: SUCCESS - if the expression is valid, 
                            the result is inside the result pointer the user sent
                  SYNTAX_ERROR - if the expression is invalid
                  MEMORY_FAIL - if memory allocation failed.
*/
calc_status_t Calculator(const char *expression, double *result);

#endif
