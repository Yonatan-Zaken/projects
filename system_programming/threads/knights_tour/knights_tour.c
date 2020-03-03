#include <stdio.h>    /* printf() */
#include <stdlib.h>   /* malloc() */
#include <pthread.h>  /* pthread_create() */

#include "bitsarray.h"

#define NUM_OF_SQUARES 64
#define NUM_OF_ROWS 8
#define NUM_OF_COLS 8

enum
{
	INVALID = -1,
	SUCCESS,
	FAIL
};

typedef int (*cmp_func_t)(const void *data1, const void *data2);

typedef struct Moves
{
	int new_pos[NUM_OF_COLS];
	size_t min_degree;
} move_t;

move_t LUT[NUM_OF_SQUARES] = {0};
/*************************************************************************/

static int CompareFunc(const void *data1, const void *data2)
{
	return (((move_t *)data1)->min_degree - ((move_t *)data2)->min_degree);
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
		column = i % NUM_OF_COLS;
		row = i / NUM_OF_ROWS;
		for (j = 0; j < NUM_OF_ROWS; ++j)
		{
			if (((column + x_moves[j]) < NUM_OF_ROWS) &&
				((column + x_moves[j]) >= 0) &&
				((row + y_moves[j]) < NUM_OF_ROWS) &&
				((row + y_moves[j]) >= 0))
			{
				LUT[i].new_pos[j] = i + x_moves[j] + (NUM_OF_ROWS * y_moves[j]);
			}
			else
			{
				LUT[i].new_pos[j] = INVALID;
			}
		}
		
		for (j = 0; j < NUM_OF_ROWS; ++j)
		{
			if (INVALID != LUT[i].new_pos[j])
			{
				++LUT[i].min_degree; 
			}
		}
		
		
	}
}

/*************************************************************************/

static int GetMinDegree(int current)
{
	size_t i = 0;
	size_t min_degree = NUM_OF_ROWS + 1; 
	int possible_pos = 0;
	
	for (i = 0; i < NUM_OF_ROWS; ++i)
	{
		if (INVALID != (possible_pos = LUT[current].new_pos[i]))
		{
			if (min_degree > LUT[possible_pos].min_degree)
			{
				min_degree = LUT[possible_pos].min_degree;
			}
		}
	}
	
	return min_degree;
}

/*************************************************************************/

static int RecSolveKT(int current, bitsarr_t board_doc, int *moves)
{
	int possible_pos = 0;
	size_t i = 0;
	board_doc = BArrSetOn(board_doc, current + 1);
	*moves = current;
	
	if (BArrSetAllBits((size_t)0) == board_doc)
	{
		return SUCCESS;
	}
	
	for (i = 0; i < NUM_OF_ROWS; ++i)
	{
		possible_pos = GetMinDegree(current);
		possible_pos = LUT[current].new_pos[i];
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
	
	if (NUM_OF_ROWS == i)
	{
		--moves;
		return FAIL;
	}
	
	return SUCCESS;
}

static int SolveKT(int first_pos, int *moves)
{
	bitsarr_t board_doc = 0;
	
	return RecSolveKT(first_pos, board_doc, moves);
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
