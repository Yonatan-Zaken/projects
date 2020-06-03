/***************************
   Generic Tests File
      Source File
   Author : Greg Markovsky
     Date : 03/01/2020            
***************************/

#include <stdio.h> /* printf */
#include <string.h> /* memcmp */
#include <sys/types.h> /* ssize_t */

#include "tests.hpp" /* PRINT_COLOR_RESET */

static size_t g_test_num = 1;
static size_t num_of_errors = 0;
static size_t num_of_errors_all = 0;

/* ---------------------------------------------------------- Test Start --- */

void TestStart(const char *name, int voc)
{
	printf("[Test #%lu - %s] ", g_test_num, name);
	++g_test_num;

	if (SILENT != voc)
	{
		printf("\n");
	}
}

/* ----------------------------------------------------------- Test End --- */

void TestEnd(const char *name, int voc)
{
	if (0 == num_of_errors)
	{
		PRINT_COLOR_SET_TO_GREEN
		printf("[SUCCESS]");
		PRINT_COLOR_RESET
		if (SILENT != voc)
		{
			printf(" - %s\n", name);
		}
	}
	else
	{
		PRINT_COLOR_SET_TO_RED
		printf("[FAILURE]");
		PRINT_COLOR_RESET
		if (SILENT != voc)
		{
			printf(" - %s\n", name);
		}

	}

	num_of_errors_all += num_of_errors;
	num_of_errors = 0;

	NEW_LINE
}

/* ---------------------------------------------------- Test Bottom Line --- */

void TestBottomLine(const char *name)
{
	if (0 == num_of_errors_all)
	{
		PRINT_COLOR_SET_TO_GREEN
		printf("[Testing %s - SUCCESS]", name);
		PRINT_COLOR_RESET
	}
	else
	{
		PRINT_COLOR_SET_TO_RED
		printf("[Testing %s - FAILURE]", name);
		PRINT_COLOR_RESET
	}

	num_of_errors_all = 0;

	NEW_LINE
	NEW_LINE
}

/* ------------------------------------------------------------ Test Int --- */

void TestInt(int voc_status, const char *str, int exp, int rec)
{
	if (exp == rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: %d, recieved: %d]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: %d, recieved: %d]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* ----------------------------------------------- Test Int Approximation --- */

void TestIntApp(int voc_status, const char *str, int exp, int rec, int margin)
{
	if (((exp + margin) >= rec) && ((exp - margin) <= rec))
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: %d - %d, recieved: %d]\n", 
			       exp - margin, exp + margin, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: %d - %d, recieved: %d]\n", 
			       exp - margin, exp + margin, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* -------------------------------------------------------- Test Not Int --- */

void TestNotInt(int voc_status, const char *str, int exp, int rec)
{
	if (exp != rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: not %d, recieved: %d]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: not %d, recieved: %d]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* --------------------------------------------------------- Test Int Pos --- */

void TestIntPos(int voc_status, const char *str, int rec)
{
	if (0 <= rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [recieved: %d]\n", rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [recieved: %d]\n", rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* --------------------------------------------------------- Test Int Neg --- */

void TestIntNeg(int voc_status, const char *str, int rec)
{
	if (0 > rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [recieved: %d]\n", rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [recieved: %d]\n", rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* --------------------------------------------------------- Test Size_t --- */

void TestSizeT(int voc_status, const char *str, size_t exp, size_t rec)
{
	if (exp == rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: %lu, recieved: %lu]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: %lu, recieved: %lu]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* -------------------------------------------------------- Test SSize_t --- */

void TestSSizeT(int voc_status, const char *str, ssize_t exp, ssize_t rec)
{
	if (exp == rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: %ld, recieved: %ld]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: %ld, recieved: %ld]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* ----------------------------------------------------- Test Size_t Hex --- */

void TestSizeTHex(int voc_status, const char *str, size_t exp, size_t rec)
{
	if (exp == rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: 0x%lx, recieved: 0x%lx]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: 0x%lx, recieved: 0x%lx]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* ------------------------------------------------- Test NOT Size_t Hex --- */

void TestNotSizeTHex(int voc_status, const char *str, size_t exp, size_t rec)
{
	if (exp != rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: not 0x%lx, recieved: 0x%lx]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: not 0x%lx, recieved: 0x%lx]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* ----------------------------------------------------------- Test Adds --- */

void TestPtr(int voc_status, const char *str, void *exp, void *rec)
{
	if (exp == rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: %p, recieved: %p]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: %p, recieved: %p]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* -------------------------------------------------------- Test Double2 --- */

void TestDouble2(int voc_status, const char *str, double exp, double rec)
{
	double min_exp = exp - 0.001;
	double max_exp = exp + 0.001;

	if ((max_exp > rec) && (min_exp < rec))
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: ~%f, recieved: ~%f]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: ~%f, recieved: ~%f]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}


/* ------------------------------------------------------- Test Not NULL --- */

void TestNotNull(int voc_status, const char *str, void *rec)
{
	if (NULL != rec)
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [%lx is not null]\n", (size_t)rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [%lx is null]\n", (size_t)rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* -------------------------------------------------------- Test Strings --- */

void TestStr(int voc_status, const char *str, const char *exp, const char *rec)
{
	if (0 == strcmp(exp, rec))
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: %s, recieved: %s]\n", exp, rec);
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: %s, recieved: %s]\n", exp, rec);
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* ---------------------------------------------------------- Test Bytes --- */

void TestBytes(int voc_status, const char *str, 
				const char *exp, const char *rec, size_t bytes)
{
	size_t i = 0;


	if (0 == memcmp(exp, rec, bytes))
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_GREEN
			printf("[SUCCESS] - %s -", str);
			printf(" [expected: ");
			for (i = 0; i < bytes; ++i)
			{
				if ('\0' == exp[i])
				{
					printf("@");
				}
				printf("%c", exp[i]);
			}
			printf("] [recieved: ");
			for (i = 0; i < bytes; ++i)
			{
				if ('\0' == rec[i])
				{
					printf("@");
				}
				printf("%c", rec[i]);
			}
			printf("]\n");
			PRINT_COLOR_RESET
		}
	}
	else
	{
		if (DETAIL == voc_status)
		{
			PRINT_COLOR_SET_TO_RED
			printf("[FAILURE] - %s -", str);
			printf(" [expected: ");
			for (i = 0; i < bytes; ++i)
			{
				if ('\0' == exp[i])
				{
					printf("@");
				}
				printf("%c", exp[i]);
			}
			printf("] [recieved: ");
			for (i = 0; i < bytes; ++i)
			{
				if ('\0' == rec[i])
				{
					printf("@");
				}
				printf("%c", rec[i]);
			}
			printf("]\n");
			PRINT_COLOR_RESET
		}
		++num_of_errors;
	}
}

/* ---------------------------------------------------------- TestIntArr --- */

void TestIntArr(int voc_status, const char *str, 
				const int *exp, const int *rec, size_t arr_size)
{
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (exp[i] == rec[i])
		{
			if (DETAIL == voc_status)
			{
				PRINT_COLOR_SET_TO_GREEN
				printf("[SUCCESS] - %s -", str);
				printf(" element #%lu -", (i + 1));
				printf(" [expected: %d, recieved: %d]\n", exp[i], rec[i]);
				PRINT_COLOR_RESET
			}
		}
		else
		{
			if (DETAIL == voc_status)
			{
				PRINT_COLOR_SET_TO_RED
				printf("[FAILURE] - %s -", str);
				printf(" element #%lu -", (i + 1));
				printf(" [expected: %d, recieved: %d]\n", exp[i], rec[i]);
				PRINT_COLOR_RESET
			}
			++num_of_errors;
		}
	}
}













