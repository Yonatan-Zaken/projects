/*********************************/
/*   			             	 */
/*   Main file DS 8              */
/*   Yonatan Zaken		         */
/*   Last Updated 10/12/19       */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "sortedlist.h" /* sorted linked list functions */
#include "dllist.h" /* doubley linked list functions */

#define UNUSED(x) (void)(x)

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

static int IsBefore(const void *node_data, const void *user_data, void *param)
{
    UNUSED(param);
    return (*(int*)node_data > *(int*)user_data);
}

static int MatchFunc(void* node_data, void* user_data)
{
    void *n = node_data;
    
    return (*(int*)n == *(int*)user_data);
}

static int AdditionFunc(void* node, void* ap)
{
    void* n = node;
    
    *(int*)n += *(int*)ap;
    
    return 0;
}

static void SortedListTest1()
{
    
    int data = 77;
    int data2 = 22;
    int data3 = 66;
    int data4 = 99;
    int data5 = 44;
    
    int x1 = 7, x2 = 8, x3 = 1, x4 = 1, x5 = 3, x6 = 3, x7 = 4;
        
    int ap = 66;
    int ap2 = 75;
    
    sll_iterator_t it1;
    sll_iterator_t it2;
    sll_iterator_t it3;
    sll_iterator_t it4;
    sll_iterator_t it5;
    sll_iterator_t it6;
    sll_iterator_t it7;
    sll_iterator_t i;
    sll_t *sll1 = NULL;
    sll_t *sll2 = NULL;
    
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
    RUN_TEST(66 == *(int*)SLLGetData(it1), "get data test3");
    it1 = SLLFind(sll1, &ap2, SLLBegin(sll1), SLLEnd(sll1));
    RUN_TEST(1 == SLLIsSameIter(it1, SLLEnd(sll1)), "is same iter");
    it1 = SLLFindBy(sll1, SLLBegin(sll1), SLLEnd(sll1), &MatchFunc, &ap);
    RUN_TEST(66 == *(int*)SLLGetData(it1), "get data test3");
    
    /* test Pop */
    RUN_TEST(99 == *(int*)SLLPopBack(sll1), "pop back test3");
    RUN_TEST(77 == *(int*)SLLPopBack(sll1), "pop back test3");
    RUN_TEST(66 == *(int*)SLLPopBack(sll1), "pop back test3");
    RUN_TEST(22 == *(int*)SLLPopBack(sll1), "pop back test3");
    
    it2 = SortLLInsert(sll1, &data2);
    it1 = SortLLInsert(sll1, &data);
    it4 = SortLLInsert(sll1, &data4);
    it5 = SortLLInsert(sll1, &data5);
    it3 = SortLLInsert(sll1, &data3);
    
    RUN_TEST(22 == *(int*)SLLPopFront(sll1), "pop front test3");
    RUN_TEST(44 == *(int*)SLLPopFront(sll1), "pop front test3");
    RUN_TEST(66 == *(int*)SLLPopFront(sll1), "pop front test3");
    RUN_TEST(77 == *(int*)SLLPopFront(sll1), "pop front test3");    
    RUN_TEST(99 == *(int*)SLLPopFront(sll1), "pop front test3");
            
    SortLLDestroy(sll1);
    
    printf("\nSorted list test4:\n");
    
    /* for each test */
    sll1 = SortLLCreate(&IsBefore, NULL);
    RUN_TEST(1 == SLLIsEmpty(sll1), "is empty test4");
    it2 = SortLLInsert(sll1, &data2);
    it1 = SortLLInsert(sll1, &data);
    it4 = SortLLInsert(sll1, &data4);
    it5 = SortLLInsert(sll1, &data5);
    it3 = SortLLInsert(sll1, &data3);
    RUN_TEST(5 == SLLSize(sll1), "size tes4");
    
    SLLForEach(SLLBegin(sll1), SLLEnd(sll1), &AdditionFunc, &ap);
    
    printf("after addition: %d\n", *(int*)SLLGetData(it2));
    printf("after addition: %d\n", *(int*)SLLGetData(it5));
    printf("after addition: %d\n", *(int*)SLLGetData(it3));
    printf("after addition: %d\n", *(int*)SLLGetData(it1));
    printf("after addition: %d\n", *(int*)SLLGetData(it4));    
    
    SortLLDestroy(sll1);
    
    printf("\nSorted list test5:\n");
    
    sll1 = SortLLCreate(&IsBefore, NULL);
    sll2 = SortLLCreate(&IsBefore, NULL);
    
    it6 = SortLLInsert(sll1, &x1);
    it6 = SortLLInsert(sll1, &x2);
    it6 = SortLLInsert(sll2, &x3);
    it6 = SortLLInsert(sll2, &x4);
    it6 = SortLLInsert(sll2, &x5);
    
    it7 = SortLLInsert(sll2, &x6);
    it7 = SortLLInsert(sll2, &x7);
    
    SLLMerge(sll2, sll1);
    RUN_TEST(7 == SLLSize(sll2), "size tes5");
    
    for (i = SLLBegin(sll2); !SLLIsSameIter(i, SLLEnd(sll2)) ; i = SLLNext(i))
    {
        printf("%d ", *(int*)SLLGetData(i));
    }
                                                                                              
    SortLLDestroy(sll1);
    SortLLDestroy(sll2);
    
    printf("\n");
}

int main()
{
    SortedListTest1();
    return 0;
}
