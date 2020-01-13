/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Caclculator                 */
/*   Author: Yonatan Zaken       */
/*   Last Updated 12/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <assert.h> /* assert */
#include <math.h>   /* pow */

#include "stack.h"
#include "arithmetic.h"

#define NUM_OF_STATES 3
#define ASCII_SIZE 255

#define UNUSED(x) (void)(x)
#define FREE(ptr) {free(ptr); ptr = NULL;} 

typedef enum Precedence
{
	ADD_AND_SUB,
	MULT_AND_DIV,
	POW
} precedence_t;

typedef struct State
{
	state_t next_state;
	func_state_t action;
} calc_state_t;

typedef struct Operator
{
	func_op_t op_handler;
	precedence_t precedence;
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
    
    if (0 == StackPush(calc->num, &number))
    {
        return NULL;
    }
    
    return runner;
}

static precedence_t PrecedenceFunc(calc_t *calc, char *expression)
{
    return calc->op_lut[(int)(*expression)].precedence;
}

char *CalcHandleOp(const char *expression, calc_t *calc)
{
    char *runner = NULL;
    precedence_t stack_operator = 0;
    precedence_t exp_operator = 0;
    char top_of_stack = 0;
    
    assert(NULL != calc);
    assert(NULL != expression);
    
    runner = (char *)expression;
    
    if (StackIsEmpty(calc->ops))
    {
        if(0 == StackPush(calc->ops, expression))
        {
            return NULL;
        }
        return (++runner);
    }
    
    top_of_stack = *(char *)StackPeek(calc->ops);
    exp_operator = calc->op_lut[(int)(*runner)].precedence;
    stack_operator = calc->op_lut[(int)top_of_stack].precedence;
    
    while ((exp_operator <= stack_operator) && !StackIsEmpty(calc->ops))
    {
        top_of_stack = *(char *)StackPeek(calc->ops);
        if ('^' == top_of_stack)
        {
            break;
        }
        stack_operator = calc->op_lut[(int)top_of_stack].precedence;    
        calc->op_lut[(int)top_of_stack].op_handler(calc);
    }
    
    StackPush(calc->ops, (void *)runner);    
    
    return (++runner);  
}

static char *EmptyFunc(const char *expression, calc_t *calc)
{
    char *runner = NULL;
        
    assert(NULL != calc);
    assert(NULL != expression);
    runner = ((char *)expression);
    
    return (++runner);
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
    
    for (i = '0'; i <= '9'; ++i)
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
       
    lut['*'].next_state = ERROR;
    lut['*'].action = &EmptyFunc;
    
    lut['/'].next_state = ERROR;
    lut['/'].action = &EmptyFunc;
    
    lut['^'].next_state = ERROR;
    lut['^'].action = &EmptyFunc;

    lut[')'].next_state = ERROR;
    lut[')'].action = &EmptyFunc;
    
    
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
        op_lut[i].precedence = 0;
    }
    
    op_lut['+'].op_handler = &AddFunc;
    op_lut['+'].precedence = ADD_AND_SUB;
    
    op_lut['-'].op_handler = &SubtractFunc;
    op_lut['-'].precedence = ADD_AND_SUB;
   
    op_lut['*'].op_handler = &MultFunc;
    op_lut['*'].precedence = MULT_AND_DIV;
    
    op_lut['/'].op_handler = &DivisionFunc;
    op_lut['/'].precedence = MULT_AND_DIV;
    
    op_lut['^'].op_handler = &PowFunc;
    op_lut['^'].precedence = POW;
    
    /*
    op_lut[')'].op_handler = 
    op_lut[')'].op_handler = 
    */
}

calc_t *CalcInit(const char *expression , double *result)
{
    calc_t *calculator = NULL;
    calc_state_t *calc_lut = NULL;
    calc_op_t *op_lut = NULL;
    stack_t *num = NULL;
    stack_t *ops = NULL;
    
    assert(NULL != expression);

    calc_lut = (calc_state_t *)malloc(NUM_OF_STATES * ASCII_SIZE
                                        * sizeof(calc_state_t));
    if (NULL != calc_lut)
    {
        InitCalcLut(calc_lut);
        op_lut = (calc_op_t *)malloc(ASCII_SIZE * sizeof(calc_op_t));
        if (NULL != op_lut)
        {
            InitOpLut(op_lut);
            num = StackCreate(sizeof(double), strlen(expression));
            if (NULL != num)
            {
                ops = StackCreate(sizeof(char), strlen(expression));
                if (NULL != ops)
                {
                    calculator = (calc_t *)malloc(sizeof(calc_t));
                    if (NULL != calculator)
                    {
                        calculator->num = num;
                        calculator->ops = ops;
                        calculator->result = result;
                        calculator->calc_lut = calc_lut;
                        calculator->op_lut = op_lut;

                        return calculator;    
                    }
                    FREE(ops);   
                }    
                FREE(num);
            }
            FREE(op_lut); 
        }
        FREE(calc_lut);
    }
    return NULL;
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
    
    while ((ERROR != status) && ('\0' != *expression))
    {
        runner = calc->calc_lut[(*runner) + status * ASCII_SIZE].
                                            action(runner, calc);
        status = calc->calc_lut[(*expression) + status * ASCII_SIZE].next_state;
        expression = runner;    
    }                                
      
    if (WAIT_FOR_OP == status)
    {
        while (!StackIsEmpty(calc->ops))
        {
            calc->op_lut[*(char*)StackPeek(calc->ops)].op_handler(calc);    
        }
        *(calc->result) = *(double*)StackPeek(calc->num);
    }
    
    else
    {
        status = ERROR;
    }
    
    return status;
}
