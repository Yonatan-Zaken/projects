/*********************************/
/*    Data Structures            */
/*    Sorted List                */       
/*    Author : Guy Cohen Zedek   */
/*    Reviewed By:               */
/*    Date: 10/12/2019           */
/*                               */
/*********************************/

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "sortedlist.h"

#define MAX_NAME 20
#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define UNUSED(x) (void)(x)
#define RUN_TEST(test)\
{\
  if(test)\
  {\
    printf(GREEN);\
    printf("SUCCESS\n");\
    printf(RESET);\
  }\
  else\
  {\
    printf(RED);\
    printf("FAIL \n");\
    printf(RESET);\
  }\
}

int PrintIterator(void *data, void *ap)
{
    UNUSED(ap);
    
    printf("%d\n", *(int *)data); 
    
    return 0; 
}

int PrintNames(void *data, void *ap)
{
    UNUSED(ap);
    
    printf("%s\n", (char *)data); 
    
    return 0; 
}

int CompareNum(const void *data1, const void *data2, void *param)
{
    UNUSED(param);
    
    return (*(const int *)data1 > *(const int *)data2);
}

int CompareByName(const void *data1, const void *data2, void *param)
{
    UNUSED(param);
    
    return (0 < strcmp((const char*)data1, (const char*)data2));  
}



struct Person
{
    char name[MAX_NAME];
    int age;
    size_t id;
};

int IsMatch(void *data, void *ap)
{
    struct Person *p = (struct Person *)data;
    return ((p->age) == *(int *)ap);
}

static void TestCreateList()
{
    int x0 = 0, x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7, x8 = 22;
    sll_t *sll, *sll2;
    sll_iterator_t it1;
    struct Person p1 = {"Guy", 22, 318434099}
                , p2 = {"Yossi", 29, 123456789}
                , p3 = {"Mati", 13, 987654321}; 
    
    printf("Sorted List 1:\n");
    sll = SortLLCreate(&CompareNum, &x0);
    RUN_TEST(1 == SLLIsEmpty(sll));
    RUN_TEST(0 == SLLSize(sll));
    
    SortLLInsert(sll, &x3);
    SortLLInsert(sll, &x1);
    SortLLInsert(sll, &x2);
    
    RUN_TEST(3 == SLLSize(sll));
    
    it1 = SLLBegin(sll);
    RUN_TEST(1 == *(int *)SLLGetData(it1));
    it1 = SLLNext(it1);
    RUN_TEST(2 == *(int *)SLLGetData(it1));
    it1 = SLLNext(it1);
    RUN_TEST(3 == *(int *)SLLGetData(it1));
    SortLLRemove(it1);
    RUN_TEST(2 == SLLSize(sll));
    
    SortLLDestroy(sll);
    
    printf("\nSorted List 2:\n");
    sll = SortLLCreate(&CompareNum, &x0);

    RUN_TEST(1 == SLLIsEmpty(sll));
    RUN_TEST(0 == SLLSize(sll));
    
    SortLLInsert(sll, &x3);
    SortLLInsert(sll, &x1);
    
    it1 = SLLPrev(SLLEnd(sll));
    
    RUN_TEST(3 == *(int *)SLLGetData(it1));
    RUN_TEST(3 == *(int *)SLLPopBack(sll));
    RUN_TEST(1 == SLLSize(sll));
    RUN_TEST(1 == *(int *)SLLPopFront(sll));
    
    SortLLDestroy(sll);
    
    printf("\nSorted List 3:\n");
    sll = SortLLCreate(&CompareNum, &x0);

    RUN_TEST(1 == SLLIsEmpty(sll));
    RUN_TEST(0 == SLLSize(sll));
    
    SortLLInsert(sll, &x6);
    SortLLInsert(sll, &x2);
    SortLLInsert(sll, &x4);
    SortLLInsert(sll, &x5);
    SortLLInsert(sll, &x3);
    SortLLInsert(sll, &x1);
    
    SLLForEach(SLLBegin(sll), SLLEnd(sll), &PrintIterator, &x0);
    
    it1 = SLLFind(sll, &x4, SLLBegin(sll), SLLEnd(sll));
    RUN_TEST(4 == *(int *)SLLGetData(it1));
    
    it1 = SLLFind(sll, &x7, SLLBegin(sll), SLLEnd(sll));
    RUN_TEST(1 == SLLIsSameIter(SLLEnd(sll), it1));
    
    SortLLDestroy(sll);
    
    printf("\nSorted List 4:\n");
    sll = SortLLCreate(&CompareByName, NULL);

    RUN_TEST(1 == SLLIsEmpty(sll));
    RUN_TEST(0 == SLLSize(sll));
    
    SortLLInsert(sll, &p3);
    SortLLInsert(sll, &p1);
    SortLLInsert(sll, &p2);

    SLLForEach(SLLBegin(sll), SLLEnd(sll), &PrintNames, NULL);
    
    it1 = SLLFindBy(sll, SLLBegin(sll), SLLEnd(sll), &IsMatch, &x8);

    RUN_TEST(22 == ((struct Person *)SLLGetData(it1))->age);
    
    it1 = SLLFindBy(sll, SLLBegin(sll), SLLEnd(sll), &IsMatch, &x1);
    
    RUN_TEST(1 == SLLIsSameIter(SLLEnd(sll), it1));
    SortLLDestroy(sll); 
    
    printf("\nSorted List 5:\n");
    sll = SortLLCreate(&CompareNum, NULL);
    sll2 = SortLLCreate(&CompareNum, NULL);
    
    SortLLInsert(sll, &x6);
    SortLLInsert(sll, &x2);
    SortLLInsert(sll, &x4);
    SortLLInsert(sll2, &x5);
    SortLLInsert(sll2, &x3);
    SortLLInsert(sll2, &x1);
    
    SLLMerge(sll, sll2);
    
    SLLForEach(SLLBegin(sll), SLLEnd(sll), &PrintIterator, &x0);
    
    RUN_TEST(6 == SLLSize(sll));
    printf("%d\n", *(int *)SLLGetData(SLLBegin(sll)));
    printf("%d\n", *(int *)SLLGetData(SLLPrev(SLLEnd(sll))));
    RUN_TEST(1 == *(int *)SLLGetData(SLLBegin(sll)));
    SortLLDestroy(sll2);
    SortLLDestroy(sll); 
}


int main()
{
    TestCreateList();
    return 0;
}
