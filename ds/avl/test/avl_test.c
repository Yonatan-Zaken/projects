/************************************************
*
* File: avl_test.c
* Ex: AVL tree
* writer: Israel Drayfus
* Description: Run and test functions of AVL tree.
*
*************************************************/

#include "utilities.h" /* TEST */
#include "avl.h"

int CmpData(const void *data1, const void *data2)
{
	return *(int *)data1 - *(int *)data2;
}

int AddOne(void *tree_data, void *param)
{
	UNUSED(param);
	
	++*(int *)tree_data;
	
	return 0;
}

int AddOne2(void *tree_data, void *param)
{
	UNUSED(param);
	
	if ( 50 < *(int *)tree_data)
	{
		return 1;
	}
	
	++*(int *)tree_data;
	
	return 0;
}

int PrintTree(void *tree_data, void *param)
{
	UNUSED(param);
	printf("%d ", *(int *)tree_data);
	
	return 0;
}

void Test1()
{
	int one = 1, two = 2;
	
	avl_t *tree = AVLCreate(CmpData);
	TEST(AVLSize(tree) == 0, "Size(), empty tree");
	TEST(AVLIsEmpty(tree) == 1, "IsEmpty(), empty tree");
	AVLDestroy(tree);
	
	tree = AVLCreate(CmpData);
	AVLInsert(tree, &one);
	TEST(AVLSize(tree) == 1, "Size(), one item int tree");
	TEST(AVLIsEmpty(tree) == 0, "IsEmpty(), one item int tree");
	TEST(AVLFind(tree, &one) == &one, "Find(), True");
	TEST(AVLFind(tree, &two) == NULL, "Find(), False");
	AVLForeach(tree, AddOne, NULL);
	TEST(one == 2, "Foreach()");
	one = 1;
	AVLRemove(tree, &two);
	TEST(AVLIsEmpty(tree) == 0, "Remove(), item not found");
	AVLRemove(tree, &one);
	TEST(AVLIsEmpty(tree) == 1, "Remove(), item found");
	AVLDestroy(tree);
	printf("\n");
}

void Test2()
{
	int one = 1, two = 2, three = 3;
	
	avl_t *tree = AVLCreate(CmpData);
	AVLInsert(tree, &one);
	AVLInsert(tree, &two);
	AVLInsert(tree, &three);
	TEST(AVLSize(tree) == 3, "Size(), 3 items in tree");
	TEST(AVLFind(tree, &two) == &two, "Find(), 3 items in tree");
	AVLForeach(tree, AddOne, NULL);
	TEST(three == 4, "Foreach()");
	AVLRemove(tree, &two);
	TEST(AVLSize(tree) == 2, "Remove(), 3 items in tree");
	AVLDestroy(tree);
	printf("\n");
}

static void TestInsert(avl_t *tree, int *a, size_t size)
{
	size_t i = 0;
	
	for(; i < size; ++i)
	{
		AVLInsert(tree, &a[i]);
	}
}

static void TestFind(avl_t *tree, int *a, size_t size)
{
	size_t i = 0;
	
	for(; i < size; ++i)
	{
		TEST(AVLFind(tree, &a[i]) == &a[i], "Find(), Test3, False");
	}
}

static void PrintArray(int *a, size_t size)
{
	size_t i = 0;
	
	for (; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

static void TestRemove(avl_t *tree, int *a, size_t size, size_t start)
{
	size_t i = 0;
	
	for (i = start; i < (size - start); ++i)
	{
		AVLRemove(tree, &a[i]);
	}
}

void ArrInit(int *a, size_t size)
{
	size_t i = 0;
	
	for (; i < size; ++i)
	{
		a[i] = i;
	}
}

void Test3()
{
	size_t size = 10;
	int a[10] = {10,20,30,40,50,60,15,35,55,65};
	avl_t *tree = AVLCreate(CmpData);
	int zero = 0;

	AVLInsert(tree, &a[2]);
	AVLInsert(tree, &a[0]);
	AVLInsert(tree, &a[1]);
	AVLInsert(tree, &a[4]);
	AVLInsert(tree, &a[3]);
	AVLInsert(tree, &a[5]);
	AVLInsert(tree, &a[6]);
	AVLInsert(tree, &a[7]);
	AVLInsert(tree, &a[8]);
	AVLInsert(tree, &a[9]);

	TEST(AVLSize(tree) == size, "Size(), Test3");
	TEST(AVLFind(tree, &zero) == NULL, "Find(), Test3, False");
	TestFind(tree, a, size);
	PrintArray(a, size);
	AVLForeach(tree, AddOne, NULL);
	PrintArray(a, size);
	AVLForeach(tree, AddOne2, NULL);
	PrintArray(a, size);
	TestRemove(tree, a, size, 0);
	AVLDestroy(tree);
	printf("\n");
}

void Test4()
{
	size_t size = 20;
	int a[20];
	avl_t *tree = AVLCreate(CmpData);
	
	ArrInit(a, size);
	TestInsert(tree, a, size);
	TEST(AVLSize(tree) == size, "Size(), 20 items in tree");
	TEST(AVLGetHeight(tree) == 4, "Balance");
	TestRemove(tree, a, size, 0);
	AVLDestroy(tree);
}

void Test5()
{
	size_t size = 1000;
	int a[1000];
	avl_t *tree = AVLCreate(CmpData);
	
	ArrInit(a, size);
	TestInsert(tree, a, size);
	TEST(AVLSize(tree) == size, "Size(), 20 items in tree");
	printf("%lu\n", AVLGetHeight(tree));
	TEST(AVLGetHeight(tree) == 9, "Balance");
	TestRemove(tree, a, size, 100);
	printf("%lu\n", AVLGetHeight(tree));
	TEST(AVLGetHeight(tree) == 7, "Balance");
	TestRemove(tree, a, size, 1);
	TEST(AVLGetHeight(tree) == 1, "Balance");
	AVLDestroy(tree);
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}











