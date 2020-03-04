/*********************************/
/*   			             	 */
/*   Algorithm		             */
/*   Knights Tour                */
/*   Author: Yonatan Zaken       */
/*   Last Updated 4/3/20         */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/
#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* malloc() */
#include <pthread.h>  /* pthread_create() */
#include <assert.h>   /* assert() */

#include "bitsarray.h"

#define NUM_OF_SQUARES 64
#define AVAILABLE_MOVES 8

enum
{
	INVALID = -1,
	SUCCESS,
	FAIL
};

typedef struct Moves
{
	int new_pos[AVAILABLE_MOVES];
	size_t degrees;
} move_t;

move_t LUT[NUM_OF_SQUARES] = {0};

/***************************************
*	     Function Prototypes  		   *
***************************************/
static void InitMovesLut();
static int GetMinDegree(int current, bitsarr_t board_doc, bitsarr_t *already_been);
static int RecSolveKT(int current, bitsarr_t board_doc, int *moves);
static int SolveKT(int first_pos, int *moves);
static void PrintPath(int *moves);

/*************************************************************************/

int main(int argc, char *argv[])
{
	int first_pos = atoi(argv[1]);
	int moves[NUM_OF_SQUARES] = {0};
	(void)argc;
	
	InitMovesLut();
	
	SolveKT(first_pos, moves);
	
	PrintPath(moves);
	
	return 0;
}

/*************************************************************************/

static void InitMovesLut()
{
	int i = 0;
	int j = 0;
	int column = 0;
	int row = 0;
	int x_moves[] = {2, 1, -1, -2, -2, -1, 1, 2};
	int y_moves[] = {1, 2, 2, 1, -1, -2, -2, -1};

	for (i = 0; i < NUM_OF_SQUARES; ++i)
	{
		column = i % AVAILABLE_MOVES;
		row = i / AVAILABLE_MOVES;
		for (j = 0; j < AVAILABLE_MOVES; ++j)
		{
			if (((column + x_moves[j]) < AVAILABLE_MOVES) &&
				((column + x_moves[j]) >= 0) &&
				((row + y_moves[j]) < AVAILABLE_MOVES) &&
				((row + y_moves[j]) >= 0))
			{
				LUT[i].new_pos[j] = i + x_moves[j] + (AVAILABLE_MOVES * y_moves[j]);
				++LUT[i].degrees; 
			}
			else
			{
				LUT[i].new_pos[j] = INVALID;
			}
		} 
	}
}

/*************************************************************************/

static int GetMinDegree(int current, bitsarr_t board_doc, bitsarr_t *already_been)
{
	size_t i = 0;
	size_t min_index = 0;
	size_t min_degree = AVAILABLE_MOVES + 1; 
	int possible_pos = 0;
	
	assert(NULL != already_been);
	
	for (i = 0; i < AVAILABLE_MOVES; ++i)
	{
	    possible_pos = LUT[current].new_pos[i];
		if ((INVALID != possible_pos) && BArrIsOff(board_doc, possible_pos + 1) &&
			 					       BArrIsOff(*already_been, possible_pos + 1))
		{
			if (min_degree > LUT[possible_pos].degrees)
			{
				min_degree = LUT[possible_pos].degrees;
				min_index = i;
			}
		}
	}
	
	if ((AVAILABLE_MOVES + 1) == min_degree)
	{
	    return INVALID;
	}
	
	*already_been = BArrSetOn(*already_been, LUT[current].new_pos[min_index] + 1);
	return LUT[current].new_pos[min_index];
}

/*************************************************************************/

static int RecSolveKT(int current, bitsarr_t board_doc, int *moves)
{
	int possible_pos = 0;
	size_t i = 0;
	bitsarr_t already_been = {0};
	
	assert(NULL != moves);
	
	board_doc = BArrSetOn(board_doc, current + 1);
	*moves = current;
	
	if (BArrSetAllBits(0) == board_doc)
	{
		return SUCCESS;
	}
	
	for (i = 0; i < AVAILABLE_MOVES; ++i)
	{
		possible_pos = GetMinDegree(current, board_doc, &already_been);
		if ((INVALID == possible_pos) || BArrIsOn(board_doc, possible_pos + 1))
		{
			continue;
		}
		else
		{
			if (SUCCESS == RecSolveKT(possible_pos, board_doc, moves + 1))
			{
				return SUCCESS;
			}
		}
	}
	
	return FAIL;
}

static int SolveKT(int first_pos, int *moves)
{
	assert(NULL != moves);
	
	return RecSolveKT(first_pos, 0, moves);
}

/*************************************************************************/

static void PrintPath(int *moves)
{
	size_t i = 0;
	
	for (i = 0; i < NUM_OF_SQUARES; ++i)
	{
		printf("step %lu: %d\n", i, moves[i]);
	}
}
