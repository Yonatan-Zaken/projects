/*
 * Author: Raz KaziRo
 * Purpose: Answares for System Programing - Fixed Size Allocator.
 * Date: 18.12.2019
 * Language: C
 * Reviewer: Ben Zaad
 */

#include <stdio.h> /*printf()*/
#include <stdlib.h> /*malloc()*/

#include "fsa.h"

#define RUN_TEST(test, errmsg)\
							{\
								if(test)\
								{\
									printf("SUCCESS\n");\
								}\
								else\
								{\
									printf("\033[1;31m");\
									printf("%s \n", errmsg);\
									printf("\033[0m");\
								}\
							}

#define UNUSED(x) (void)(x)
#define FREE(ptr) free(ptr); ptr = NULL;

struct FixedSizeAllocator
{
	size_t next_available_index;
	size_t block_size;
	size_t segment_size;
};

struct BlockHeader
{
	size_t next_free_index;
};

void TestFSASuggestSize()
{
	RUN_TEST(47 == FSASuggestSize(1, 8), "FAIL: WRONG SIZE");

	printf("\n");
}

void TestFSAInit()
{	
	
	size_t segment_size = FSASuggestSize(10, 4);
	int *allocation = (int *)malloc(segment_size);
	fsa_t *new_fsa = FSAInit(allocation, segment_size, 4);

	RUN_TEST(10 == FSACountFree(new_fsa), "FAIL WRONG SIZE (10)");
	FREE(allocation);
	
	printf("\n");
}

void TestFSAAlloc()
{	
	
	size_t segment_size = FSASuggestSize(2, 4);
	int *allocation = (int *)malloc(segment_size);
	fsa_t *new_fsa = FSAInit(allocation, segment_size, 4);
	struct BlockHeader block1_header_value;
	struct BlockHeader block2_header_value;


	void *block1 = FSAAlloc(new_fsa);
	void *block2 = FSAAlloc(new_fsa);

	block1 = (char *)block1 -8;
	block2 = (char *)block2 -8;

	block1_header_value = *(struct BlockHeader *)block1;
	block2_header_value = *(struct BlockHeader *)block2;

	RUN_TEST(32 == block1_header_value.next_free_index, "FAIL: WRONG RETURNED VALUE (24)");
	RUN_TEST(48 == block2_header_value.next_free_index, "FAIL: WRONG RETURNED VALUE (40)");

	FREE(allocation);

	printf("\n");
}

void TestFSACountFree()
{
	size_t segment_size = FSASuggestSize(2, 4);
	int *allocation = (int *)malloc(segment_size);
	fsa_t *new_fsa = FSAInit(allocation, segment_size, 4);

	void *block1 = NULL;
	void *block2 = NULL;


	RUN_TEST(2 == FSACountFree(new_fsa), "FAIL WRONG SIZE (2)");
	block1 = FSAAlloc(new_fsa);
	RUN_TEST(1 == FSACountFree(new_fsa), "FAIL WRONG SIZE (1)");
	block2 = FSAAlloc(new_fsa);
	RUN_TEST(0 == FSACountFree(new_fsa), "FAIL WRONG SIZE (0)");

	FREE(allocation);

	printf("\n");

}

void TestFSAFree()
{
	size_t segment_size = FSASuggestSize(2, 4);
	int *allocation = (int *)malloc(segment_size);
	fsa_t *new_fsa = FSAInit(allocation, segment_size, 4);

	void *block1 = FSAAlloc(new_fsa);
	void *block2 = FSAAlloc(new_fsa);

	RUN_TEST(0 == FSACountFree(new_fsa), "FAIL WRONG SIZE (0)");
	FSAFree(block2);
	RUN_TEST(1 == FSACountFree(new_fsa), "FAIL WRONG SIZE (1)");
	FSAFree(block1);
	RUN_TEST(2 == FSACountFree(new_fsa), "FAIL WRONG SIZE (2)");

	FREE(allocation);

	printf("\n");

}

int main(int argc, char const *argv[])
{
	printf("TestFSASuggestSize()\n");
	TestFSASuggestSize();

	printf("TestFSAInit()\n");
	TestFSAInit();
	
	printf("TestFSAAlloc()\n");
	TestFSAAlloc();

	printf("TestFSACountFree()\n");
	TestFSACountFree();

	printf("TestFSAFree()\n");
	TestFSAFree();

	UNUSED(argv);
	UNUSED(argc);
	return 0;
}
