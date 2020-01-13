#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

typedef enum States
{
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	ERROR
} state_t;

typedef struct Calc calc_t;

typedef int (*func_op_t)(calc_t *calculator);
typedef char* (*func_state_t)(const char *expression, calc_t *calculator);

/* Initiates LUT of all ASCII table 
	pointer to calculator struct or NULL for memory fail */
calc_t *CalcInit(const char *expression, double *result);

/* free all resorces in use */ 
void CalcDestroy(calc_t *calc);

state_t CalcRun(const char *expression, calc_t *calc);

char *CalcHandleNum(const char *expression, calc_t *calc);

char *CalcHandleOp(const char *expression, calc_t *calc);

#endif
