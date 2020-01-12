/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Caclculator          */
/*   Author: Yonatan Zaken       */
/*   Last Updated 12/1/20         */
/*   Reviewed by:           */   
/*			                   	 */
/*********************************/
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "stack.h"
#include "arithmetic.h"

#define NUM_OF_STATES 3
#define ASCII_SIZE 255

#define UNUSED(x) (void)(x)
#define FREE(ptr) {free(ptr); ptr = NULL;} 

typedef struct State
{
	state_t next_state;
	func_state_t action;
} calc_state_t;

typedef struct Operator
{
	func_op_t op_handler;
	int presedence;
} calc_op_t;

struct Calc
{
	stack_t *num;
	stack_t *ops;
	double *result;
	calc_state_t *calc_lut;
	calc_op_t *op_lut;
};

char *CalcHandleNum(const char *expression, calc_t *calc)
{
    char *runner = NULL;
    double number = 0;
    
    assert(NULL != calc);
    assert(NULL != expression);
    
    runner = (char *)expression;
    number = strtod(runner, &runner);
    
    if (StackPush(calc->num, &number));
    {
        return NULL;
    }
    
    expression = runner;
    return expression;
}

char *CalcHandleOp(const char *expression, calc_t *calc)
{

}

static char *EmptyFunc(const char *expression, calc_t *calc)
{    
    assert(NULL != calc);
    assert(NULL != expression);
    
    return (++expression);
}

static int EmptyAritFunc(calc_t *calc)
{

}

static int AddFunc(calc_t *calc)
{
    double a, b, c = 0;
    
    assert(NULL != calc);
    
    a = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    b = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    StackPop(calc->ops);
    c = b + a;
    
    return StackPush(calc->num, (const void *)&c);
}

static int SubtractFunc(calc_t *calc)
{
    double a, b, c = 0;
    
    assert(NULL != calc);
    
    a = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    b = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    StackPop(calc->ops);
    c = b - a;
    
    return StackPush(calc->num, (const void *)&c);
}

static int MultFunc(calc_t *calc)
{
    double a, b, c = 0;
    
    assert(NULL != calc);
    
    a = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    b = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    StackPop(calc->ops);
    c = b * a;
    
    return StackPush(calc->num, (const void *)&c);
}

static int DivisionFunc(calc_t *calc)
{
    double a, b, c = 0;
    
    assert(NULL != calc);
    
    a = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    b = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    StackPop(calc->ops);
    c = b / a;
    
    return StackPush(calc->num, (const void *)&c);
}

static int PowFunc(calc_t *calc)
{

    double a, b, c = 0;
    
    assert(NULL != calc);
    
    a = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    b = *(double *)StackPeek(calc->num);
    StackPop(calc->num);
    StackPop(calc->ops);
    c = pow(b, a);
    
    return StackPush(calc->num, (const void *)&c);
}


static void InitCalcLut(calc_state_t *lut)
{
    int i = 0;
    for (i = 0; i < NUM_OF_STATES * ASCII_SIZE; ++i)
    {
        lut[i].next_state = ERROR;
        lut[i].action = &EmptyFunc;
    }
    
    /* State 1 wait for num */
    
    for (i = 0; i < 10; ++i)
    {
        lut[i].next_state = WAIT_FOR_OP;
        lut[i].action = &CalcHandleNum;
    }
    
    lut['+'].next_state = WAIT_FOR_OP;
    lut['+'].action = &CalcHandleNum;
    
    lut['-'].next_state = WAIT_FOR_OP;
    lut['-'].action = &CalcHandleNum;
    
    lut['.'].next_state = WAIT_FOR_OP;
    lut['.'].action = &CalcHandleNum;
    
    lut[' '].next_state = WAIT_FOR_NUM;
    lut[' '].action = &EmptyFunc;
    
    lut['('].next_state = WAIT_FOR_NUM;
    lut['('].action = &EmptyFunc;
    
/*    
    lut['*'].next_state = ERROR;
    lut['*'].action = &ErrorEmptyFunc;
    
    lut['/'].next_state = ERROR;
    lut['/'].action = &ErrorEmptyFunc;
    
    lut['^'].next_state = ERROR;
    lut['^'].action = &ErrorEmptyFunc;

    lut[')'].next_state = ERROR;
    lut[')'].action = &ErrorEmptyFunc;
    
    lut['*'].next_state = ERROR;
    lut['*'].action = &ErrorEmptyFunc;
*/

    lut['*' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    lut['*' + ASCII_SIZE].action = &CalcHandleOp;
    
    lut['/' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    lut['/' + ASCII_SIZE].action = &CalcHandleOp;
    
    lut['^' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    lut['^' + ASCII_SIZE].action = &CalcHandleOp;
    
    lut['+' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    lut['+' + ASCII_SIZE].action = &CalcHandleOp;
    
    lut['-' + ASCII_SIZE].next_state = WAIT_FOR_NUM;
    lut['-' + ASCII_SIZE].action = &CalcHandleOp;
    
    lut[' ' + ASCII_SIZE].next_state = WAIT_FOR_OP;
    lut[' ' + ASCII_SIZE].action = &EmptyFunc;
    
    lut[')' + ASCII_SIZE].next_state = WAIT_FOR_OP;
    /*lut[')' + ASCII_SIZE].action = &;  WHAT TO DO HERE? */
    
}

static void InitOpLut(calc_op_t *op_lut)
{
    int i = 0;
    for (i = 0; i < ASCII_SIZE; ++i)
    {
        op_lut[i].op_handler = &EmptyAritFunc;
        op_lut[i].presedence = 0;
    }
    
    op_lut['+'].op_handler = &AddFunc;
    op_lut['+'].presedence = 0;
    
    op_lut['-'].op_handler = &SubtractFunc;
    op_lut['-'].presedence = 0;
   
    op_lut['*'].op_handler = &MultFunc;
    op_lut['*'].presedence = 1;
    
    op_lut['/'].op_handler = &DivisionFunc;
    op_lut['/'].presedence = 1;
    
    op_lut['^'].op_handler = &PowFunc;
    op_lut['^'].presedence = 2;
    
    /*
    op_lut[')'].op_handler = 
    op_lut[')'].op_handler = 
    */
}

calc_t *CalcInit(const char *expression)
{
    calc_t *calculator = NULL;
    calc_state_t *calc_lut = NULL;
    calc_op_t *op_lut = NULL;
    stack_t *num = NULL;
    stack_t *ops = NULL;
    
    assert(NULL != expression);
    
    calc_lut = (calc_state_t *)malloc(NUM_OF_STATES * ASCII_SIZE
                                                      * sizeof(calc_state_t));
    if (NULL == calc_lut)
    {
        return NULL;   
    }
    
    op_lut = (calc_op_t *)malloc(ASCII_SIZE * sizeof(calc_op_t));
    if (NULL == op_lut)
    {
        FREE(calc_lut);
        return NULL;
    }
    
    num = StackCreate(sizeof(char), strlen(expression));
    if (NULL == num)
    {
        FREE(calc_lut);
        FREE(op_lut);
        return NULL;
    }
    
    ops = StackCreate(sizeof(char), strlen(expression));
    if (NULL == ops)
    {
        FREE(calc_lut);
        FREE(op_lut);
        FREE(num);
        return NULL;    
    }
    
    calculator = (calc_t *)malloc(sizeof(calc_t));
    if (NULL == calculator)
    {
        FREE(calc_lut);
        FREE(op_lut);
        FREE(num);
        FREE(ops);
        return NULL;
    }
    
    calculator->num = num;
    calculator->ops = ops;
    calculator->result = NULL;
    calculator->calc_lut = calc_lut;
    calculator->op_lut = op_lut;
    
    return calculator;
}

void CalcDestroy(calc_t *calc)
{
    FREE(calc->calc_lut);
    FREE(calc->op_lut);
    StackDestroy(calc->num);
    StackDestroy(calc->ops);
    FREE(calc);
}

state_t CalcRun(const char *expression, calc_t *calc)
{
    state_t status = WAIT_FOR_NUM;
    char *runner = NULL;
    
    assert(NULL != calc);
    assert(NULL != expression);
    
    status = WAIT_FOR_NUM;
    runner = (char *)expression;
    
    while (ERROR != status)
    {
        runner = calc->calc_lut[(*runner) + status * ASCII_SIZE].
                                            action(runner, calc);
        status = calc->calc_lut[(*expression) + status * ASCII_SIZE].next_state;
        expression = runner;    
    }
}
