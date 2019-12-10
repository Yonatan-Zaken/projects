/*********************************/
/*   			             	 */
/*   Main file DS 9              */
/*   Yonatan Zaken		         */
/*   Last Updated 10/12/19       */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "sortedlist.h" /* sorted linked list functions */
#include "dllist.h" /* doubley linked list functions */

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

static int IsBefore(const void *node_data,const void *user_data, void *param)
{
    return (*(int*)user_data < *(int*)node_data);
}

static int MatchFunc(void* node_data, void* user_data)
{
    void *n = node_data;
    
    return (*(int*)n == *(int*)user_data);
}

static void SortedListTest1()
{
    
    int data = 77;
    int data2 = 22;
    int data3 = 66;
    int data4 = 99;
    int ap = 66;
    
    sll_iterator_t it1;
    sll_iterator_t it2;
    sll_iterator_t it3;
    sll_iterator_t it4;
    sll_t *sll1 = NULL;
    
    printf("Sorted list test1:\n");
    
    sll1 = SortLLCreate(&IsBefore, NULL);
    RUN_TEST(1 == SLLIsEmpty(sll1), "is empty test1");
    it1 = SortLLInsert(sll1, &data);
    RUN_TEST(1 == SLLSize(sll1), "size tes1");
    RUN_TEST(77 == *(int*)SLLGetData(it1), "get data test1");
    RUN_TEST(1 == SLLIsSameIter(it1, it1), "same iter test1");
    
    SortLLDestroy(sll1);
    
    printf("\nSorted list test2:\n");
    /* test SLLInsert */
    sll1 = SortLLCreate(&IsBefore, NULL);
    RUN_TEST(1 == SLLIsEmpty(sll1), "is empty test2");
    it1 = SortLLInsert(sll1, &data);
    it2 = SortLLInsert(sll1, &data2);
    it3 = SortLLInsert(sll1, &data3);
    RUN_TEST(3 == SLLSize(sll1), "size tes2");
    RUN_TEST(77 == *(int*)SLLGetData(it1), "get data test2");
    RUN_TEST(22 == *(int*)SLLGetData(it2), "get data test2");
    RUN_TEST(66 == *(int*)SLLGetData(it3), "get data test2");
    
    SortLLDestroy(sll1);
    
    printf("\nSorted list test3:\n");
    /* test SLLFind */
    sll1 = SortLLCreate(&IsBefore, NULL);
    RUN_TEST(1 == SLLIsEmpty(sll1), "is empty test3");
    it1 = SortLLInsert(sll1, &data);
    it2 = SortLLInsert(sll1, &data2);
    it3 = SortLLInsert(sll1, &data3);
    it4 = SortLLInsert(sll1, &data4);
    RUN_TEST(4 == SLLSize(sll1), "size tes3");
    
    it1 = SLLFind(sll1, &ap, SLLBegin(sll1), SLLEnd(sll1));
    RUN_TEST(77 == *(int*)SLLGetData(it1), "get data test3");
    it1 = SLLFindBy(sll1, SLLBegin(sll1), SLLEnd(sll1), &MatchFunc, &ap);
    RUN_TEST(66 == *(int*)SLLGetData(it1), "get data test3");
    
    /* test Pop */
    RUN_TEST(99 == *(int*)SLLPopBack(sll1), "pop back test3");
    RUN_TEST(77 == *(int*)SLLPopBack(sll1), "pop back test3");
    RUN_TEST(66 == *(int*)SLLPopBack(sll1), "pop back test3");
    RUN_TEST(22 == *(int*)SLLPopBack(sll1), "pop back test3");
    
    SortLLDestroy(sll1);
    printf("\n");
}

int main()
{
    SortedListTest1();
    return 0;
}
