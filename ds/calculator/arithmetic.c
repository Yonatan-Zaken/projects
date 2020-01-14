/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Caclculator                 */
/*   Author: Yonatan Zaken       */
/*   Last Updated 14/1/20        */
/*   Reviewed by: Raz            */   
/*			                   	 */
/*********************************/
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <assert.h> /* assert */
#include <math.h>   /* pow */

#include "stack.h"
#include "arithmetic.h"

#define NUM_OF_STATES 3
#define ASCII_SIZE 256 

#define UNUSED(x) (void)(x)
#define FREE(ptr) {free(ptr); ptr = NULL;} 

typedef enum Precedence
{
    OPEN_PARENTHESES,
    CLOSE_PARENTHESES,
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

char *CalcHandleOp(const char *expression, calc_t *calc)
{
    char *runner = NULL;
    
    assert(NULL != calc);
    assert(NULL != expression);
    
    runner = (char *)expression;

    while (!StackIsEmpty(calc->ops) && 
          (calc->op_lut[(int)(*runner)].precedence <= 
           calc->op_lut[(int)*(char *)StackPeek(calc->ops)].precedence))
    {
        if (('^' == *(char *)StackPeek(calc->ops)) && ('^' == *runner))
        {
            break;
        }
     
        calc->op_lut[(int)*(char *)StackPeek(calc->ops)].op_handler(calc);  
    }
    
    StackPush(calc->ops, runner); 
    return (++runner);  
}

static char *ParenthesesHandle(const char *expression, calc_t *calc)
{
    char *runner = NULL;
    
    assert(NULL != calc);
    
    runner = (char *)expression;
    
    if ('(' == *runner)
    {
        StackPush(calc->ops, runner);
    }
    
    else 
    {
        CalcHandleOp(expression, calc);
        StackPop(calc->ops);
        StackPop(calc->ops);
    }
    
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
    UNUSED(calc);
    return 0;
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
           
    lut['*'].next_state = ERROR;
    lut['*'].action = &EmptyFunc;
    
    lut['/'].next_state = ERROR;
    lut['/'].action = &EmptyFunc;
    
    lut['^'].next_state = ERROR;
    lut['^'].action = &EmptyFunc;

    lut['('].next_state = WAIT_FOR_NUM;
    lut['('].action = &ParenthesesHandle;

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
    
    lut['(' + ASCII_SIZE].next_state = ERROR;
    lut['(' + ASCII_SIZE].action = &EmptyFunc;
    
    lut[')' + ASCII_SIZE].next_state = WAIT_FOR_OP;
    lut[')' + ASCII_SIZE].action = &ParenthesesHandle;
       
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
    
    op_lut['('].op_handler = &EmptyAritFunc;
    op_lut['('].precedence = OPEN_PARENTHESES;
    
    op_lut[')'].op_handler = &EmptyAritFunc;
    op_lut[')'].precedence = CLOSE_PARENTHESES;
}

calc_t *CalcInit(const char *expression , double *result)
{
    calc_t *calculator = NULL; 
    
    assert(NULL != expression);
    
    calculator = (calc_t *)malloc(sizeof(calc_t));
    if (NULL != calculator)
    {
        calculator->num = StackCreate(sizeof(double), strlen(expression));
        if (NULL != calculator->num)
        {
            calculator->ops = StackCreate(sizeof(char), strlen(expression));
            if (NULL != calculator->ops)
            {
                calculator->calc_lut = (calc_state_t *)malloc(ASCII_SIZE
                                * NUM_OF_STATES * sizeof(calc_state_t));
                if (NULL != calculator->calc_lut)
                {
                    InitCalcLut(calculator->calc_lut);
                    calculator->op_lut = (calc_op_t *)malloc(ASCII_SIZE *
                                                      sizeof(calc_op_t));
                    if (NULL != calculator->op_lut)
                    {
                        InitOpLut(calculator->op_lut);
                        calculator->result = result;
                        return calculator;
                    }
                    FREE(calculator->op_lut);
                }
                FREE(calculator->ops);
            }
            FREE(calculator->num);
        }
        FREE(calculator);
    }
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
        while (1 < StackSize(calc->num))
        {
            calc->op_lut[(int)*(char*)StackPeek(calc->ops)].op_handler(calc);    
        }
        
        *(calc->result) = *(double*)StackPeek(calc->num);
    }
    
    else
    {
        status = ERROR;
    }
    
    return status;
}
