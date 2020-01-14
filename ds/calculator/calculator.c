/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Caclculator                 */
/*   Author: Yonatan Zaken       */
/*   Last Updated 14/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/
#include <stdlib.h> /* NULL */
#include <assert.h> /* assert */

#include "arithmetic.h"
#include "calculator.h"

calc_status_t Calculator(const char *expression, double *result)
{
    calc_t *calculator = NULL;
    state_t state = WAIT_FOR_NUM;
    calc_status_t status = SUCCESS;  
    
    assert(NULL != expression);
        
    calculator = CalcInit(expression, result);
    if (NULL == calculator)
    {
        return MEMORY_FAIL;
    } 
    
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
