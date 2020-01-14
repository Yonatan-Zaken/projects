/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Caclculator                 */
/*   Author: Yonatan Zaken       */
/*   Last Updated 12/1/20         */
/*   Reviewed by:           */   
/*			                   	 */
/*********************************/
#include <stdlib.h>
#include <assert.h>

#include "arithmetic.h"
#include "calculator.h"

calc_status_t Calculator(const char *expression, double *result)
{
    calc_t *calculator = NULL;
    state_t state = 0; /*RAZ - USE THE ENUM NAME FOR SIMPLICITY*/
    calc_status_t status = 0;  /*RAZ - USE THE ENUM NAME FOR SIMPLICITY*/
    
    assert(NULL != expression);
        
    calculator = CalcInit(expression, result); /*RAZ - NEED TO CHECK IF INIT NOT FAILED BEFORE RUN*/
    state = CalcRun(expression, calculator);
    if (WAIT_FOR_OP == state)
    {
        status = SUCCESS; 
    }
    else
    {
        status = SYNTAX_ERROR;
    }
    CalcDestroy(calculator);
    
    return status;
}

