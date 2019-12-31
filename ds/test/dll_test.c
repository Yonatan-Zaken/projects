/*********************************/
/*   			             	 */
/*   Main file DS 7              */
/*   Yonatan Zaken		         */
/*   Last Updated 9/12/19        */
/*   Reviewed by: Itai           */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

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

static int AdditionFunc(void* node, void* ap)
{
    void* n = node;
    
    *(int*)n += *(int*)ap;
    
    return 0;
}

static int MatchFunc(void* node, void* ap)
{
    void *n = node;
    
    return (*(int*)n == *(int*)ap);
}

static void TestDLL1()
{
    int data = 77;
    int data2 = 22;
    int data3 = 66;
    int data4 = 11;
    int data5 = 33;
    
    int ap = 3;
    iterator_t it1;
    iterator_t it2;
    iterator_t it3;
    iterator_t it4;
    iterator_t it5;
    dll_t *dll1 = NULL;
    dll_t *dll2 = NULL;
    dll_t *dll3 = NULL;
    
    printf("DLL test 1:\n");
    
    dll1 = DLLCreate();
    it1 = DLLEnd(dll1);
    
    RUN_TEST(1 == DLLIsEmpty(dll1), "is empty test1");
    it1 = DLLInsert(dll1, it1, &data);
    RUN_TEST(1 == DLLSize(dll1), "size test1");
    RUN_TEST(0 == DLLIsEmpty(dll1), "is empty test1");
    it1 = DLLRemove(it1);
    RUN_TEST(1 == DLLIsEmpty(dll1), "is empty test1");
    it1 = DLLInsert(dll1, it1, &data);
    it2 = DLLInsert(dll1, it1, &data2);
    it3 = DLLInsert(dll1, it2, &data3);
    RUN_TEST(3 == DLLSize(dll1), "size test1");    
    RUN_TEST(77 == *(int*)DLLGetData(it1), "get data test1");
    RUN_TEST(22 == *(int*)DLLGetData(it2), "get data test1");
    RUN_TEST(66 == *(int*)DLLGetData(it3), "get data test1");
    RUN_TEST(1 == DLLIsSameIter(it1, it1), "is same iter test1");
    DLLDestroy(dll1);
    
    printf("\nDLL test 2:\n");
    
    dll2 = DLLCreate();
    RUN_TEST(1 == DLLIsEmpty(dll2), "is empty test2");
    it1 = DLLPushBack(dll2, &data);
    it2 = DLLPushBack(dll2, &data2);
    it3 = DLLPushBack(dll2, &data3);
    RUN_TEST(3 == DLLSize(dll2), "size test2");
    RUN_TEST(77 == *(int*)DLLGetData(it1), "get data test1");
    RUN_TEST(22 == *(int*)DLLGetData(it2), "get data test1");
    RUN_TEST(66 == *(int*)DLLGetData(it3), "get data test1");
    RUN_TEST(66 == *(int*)DLLPopBack(dll2), "pop back test2");
    RUN_TEST(22 == *(int*)DLLPopBack(dll2), "pop back test2");
    RUN_TEST(77 == *(int*)DLLPopBack(dll2), "pop back test2");
    
    it1 = DLLPushFront(dll2, &data);
    it2 = DLLPushFront(dll2, &data2);
    it2 = DLLPushFront(dll2, &data3);
    RUN_TEST(3 == DLLSize(dll2), "size test2");
    RUN_TEST(66 == *(int*)DLLPopFront(dll2), "pop front test2");
    RUN_TEST(22 == *(int*)DLLPopFront(dll2), "pop front test2");

    DLLDestroy(dll2);
    
    printf("\nDLL test 3:\n");
    
    dll2 = DLLCreate();
    RUN_TEST(1 == DLLIsEmpty(dll2), "is empty test3");
    it1 = DLLPushBack(dll2, &data);
    it2 = DLLPushBack(dll2, &data2);
    it3 = DLLPushBack(dll2, &data3);
    RUN_TEST(3 == DLLSize(dll2), "is empty test3");    
    
    RUN_TEST(0 == DLLForEach(it1, it3, &AdditionFunc, &ap), "for each test3");
    RUN_TEST(80 == *(int*)DLLPopFront(dll2), "pop back test3");
    RUN_TEST(25 == *(int*)DLLPopFront(dll2), "pop back test3");
    
    DLLDestroy(dll2);
    
    printf("\nDLL test 4:\n");
    
    dll2 = DLLCreate();
    RUN_TEST(1 == DLLIsEmpty(dll2), "is empty test4");
    it1 = DLLPushBack(dll2, &data);
    it2 = DLLPushBack(dll2, &data2);
    it3 = DLLPushBack(dll2, &data3);
    RUN_TEST(3 == DLLSize(dll2), "is empty test4");    
    
    it4 = DLLFind(it1, it3, &MatchFunc, &data2);
    RUN_TEST(25 == *(int*)DLLGetData(it4), "get data test4"); /* data2 is now 25*/
    
    DLLDestroy(dll2);
    
    printf("\nDLL test 5:\n");
    dll2 = DLLCreate();
    dll3 = DLLCreate();
    
    it1 = DLLPushBack(dll2, &data);
    it2 = DLLPushBack(dll2, &data2);
    it3 = DLLPushBack(dll2, &data3);
    it4 = DLLPushBack(dll2, &data4);
    
    it5 = DLLPushBack(dll3, &data5);
    
    DLLSplice(it1, it4, it5);
    RUN_TEST(4 == DLLSize(dll3), "size test5 after splice");
    
    DLLDestroy(dll2);
    DLLDestroy(dll3);
    printf("\n");
}

int main()
{
    TestDLL1();
    
    return 0;
}
