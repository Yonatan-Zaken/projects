#include <stdio.h> /* printf */
#include <string.h> /* memcmp */
#include <stdint.h> /* uint64_t */

#define PRINT_COLOR_SET_TO_RED printf("\x1b[31m");
#define PRINT_COLOR_SET_TO_GREEN printf("\x1b[32m");
#define PRINT_COLOR_RESET printf("\x1b[0m");

void TestInt(const char *func, int exp, int rec);
void TestSizeT(const char *func, size_t exp, size_t rec);

void TestInt(const char *func, int exp, int rec)
{
	if (exp == rec)
	{
		PRINT_COLOR_SET_TO_GREEN
		printf("[SUCCESS] - %s ", func);
		printf(" [expected: %d, recieved: %d]\n", exp, rec);
		PRINT_COLOR_RESET
	}
	else
	{
		PRINT_COLOR_SET_TO_RED
		printf("[FAILURE] - %s", func);
		printf(" [expected: %d, recieved: %d]\n", exp, rec);
		PRINT_COLOR_RESET
	}
}

void TestSizeT(const char *func, size_t exp, size_t rec)
{
	if (exp == rec)
	{
		PRINT_COLOR_SET_TO_GREEN
		printf("[SUCCESS] - %s", func);
		printf(" [expected: %lu, recieved: %lu]\n", exp, rec);
		PRINT_COLOR_RESET
	}
	else
	{
		PRINT_COLOR_SET_TO_RED
		printf("[FAILURE] - %s", func);
		printf(" [expected: %lu, recieved: %lu]\n", exp, rec);
		PRINT_COLOR_RESET
	}
}
