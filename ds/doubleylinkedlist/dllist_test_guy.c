/*********************************/
/*    Data Structures            */
/*    Double Linked List         */       
/*    Author : Guy Cohen Zedek   */
/*    Reviewed By:               */
/*    Date: 8/12/2019            */
/*                               */
/*********************************/

#include <stdio.h>
#include <stdlib.h>

#include "dllist.h"

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

int IsMatch(void *data, void *ap)
{
    return (*(int *)data == *(int *)ap);
}

static void TestCreateDLL()
{
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7;
    dll_t *dll, *dll2;   
    iterator_t it, it2, it_start, it_end, it_find;
    
    printf("Double Linked List 1:\n");

    dll = DLLCreate();
    RUN_TEST(0 == DLLSize(dll));
    RUN_TEST(1 == DLLIsEmpty(dll));
    
    DLLPushBack(dll, &x1);
    it = DLLBegin(dll);
    RUN_TEST(1 == *(int *)DLLGetData(it));
    
    DLLPushBack(dll, &x2);
    it = DLLGetNext(it);
    RUN_TEST(2 == *(int *)DLLGetData(it));
    
    DLLPushBack(dll, &x3);
    it = DLLGetNext(it);
    RUN_TEST(3 == *(int *)DLLGetData(it));
    
    DLLPushFront(dll, &x4);
    it = DLLGetPrev(it);
    it = DLLGetPrev(it);
    it = DLLGetPrev(it);
    RUN_TEST(4 == *(int *)DLLGetData(it));
    
    DLLPushBack(dll, &x5);    
    it = DLLGetNext(it);
    it = DLLGetNext(it);
    it = DLLGetNext(it);
    it = DLLGetNext(it);
    RUN_TEST(5 == *(int *)DLLGetData(it));
    RUN_TEST(5 == DLLSize(dll));
    RUN_TEST(0 == DLLIsEmpty(dll));
    RUN_TEST(4 == *(int *)DLLPopFront(dll));
    RUN_TEST(4 == DLLSize(dll));
    RUN_TEST(5 == *(int *)DLLPopBack(dll));
    RUN_TEST(3 == DLLSize(dll));
    RUN_TEST(1 == *(int *)DLLPopFront(dll));
    RUN_TEST(2 == DLLSize(dll));
    RUN_TEST(3 == *(int *)DLLPopBack(dll));
    RUN_TEST(1 == DLLSize(dll));
    RUN_TEST(2 == *(int *)DLLPopFront(dll));
    RUN_TEST(0 == DLLSize(dll));
    RUN_TEST(1 == DLLIsEmpty(dll));
    
    DLLDestroy(dll);    
    
    printf("\nDouble Linked List 2:\n");
    
    dll = DLLCreate();   
    RUN_TEST(0 == DLLSize(dll));
    RUN_TEST(1 == DLLIsEmpty(dll));
    
    DLLPushBack(dll, &x1);
    it = DLLBegin(dll);
    it2 = DLLBegin(dll);
    RUN_TEST(1 == DLLIsSameIter(it, it2));
    RUN_TEST(1 == *(int *)DLLGetData(it));
    
    DLLPushBack(dll, &x2);
    it = DLLGetNext(it);
    RUN_TEST(2 == *(int *)DLLGetData(it));
    
    DLLPushBack(dll, &x3);
    it = DLLGetNext(it);
    RUN_TEST(3 == *(int *)DLLGetData(it));
    
    it = DLLGetPrev(it);
    RUN_TEST(3 == *(int *)DLLGetData(DLLRemove(it)));
    
    DLLDestroy(dll);
    
    printf("\nDouble Linked List 3:\n");    
    
    dll = DLLCreate();
    dll2 = DLLCreate();   
    
    RUN_TEST(0 == DLLSize(dll));
    RUN_TEST(1 == DLLIsEmpty(dll));
    
    DLLPushBack(dll, &x1);
    DLLPushBack(dll, &x2);
    DLLPushBack(dll, &x3);
    DLLPushBack(dll, &x4);
    DLLPushBack(dll, &x5);
    it = DLLBegin(dll);
    it_start = DLLGetNext(it);
    it_end = DLLGetPrev(DLLEnd(dll));
    
    DLLForEach(it_start, it_end, &PrintIterator, &x1);
    
    DLLPushBack(dll2, &x6);
    DLLPushBack(dll2, &x7);
    it2 = DLLBegin(dll2);
    
    it2 = DLLSplice(it_start, it_end, it2);
    RUN_TEST(5 == DLLSize(dll2));
    RUN_TEST(2 == DLLSize(dll));
    RUN_TEST(6 == *(int *)DLLGetData(it2));
    RUN_TEST(7 == *(int *)DLLGetData(DLLGetPrev(DLLEnd(dll2))));
    
    DLLDestroy(dll);
    DLLDestroy(dll2);
    
    printf("\nDouble Linked List 4:\n");    
    
    dll = DLLCreate();
    dll2 = DLLCreate();   
    
    RUN_TEST(0 == DLLSize(dll));
    RUN_TEST(1 == DLLIsEmpty(dll));
    
    DLLPushBack(dll, &x1);
    DLLPushBack(dll, &x2);
    DLLPushBack(dll, &x3);
    DLLPushBack(dll, &x4);
    DLLPushBack(dll, &x5);
    it_start = DLLBegin(dll);
    it_end = DLLEnd(dll);
    it_find = it_start;
    it_find = DLLGetNext(it_find);
    it_find = DLLGetNext(it_find);
    it_find = DLLGetNext(it_find);
    
    DLLForEach(it_start, it_end, &PrintIterator, &x1);
    RUN_TEST(1 == DLLIsSameIter(it_find, DLLFind(it_start, it_end, &IsMatch, &x4)));
    RUN_TEST(1 == DLLIsSameIter(it_end, DLLFind(it_start, it_end, &IsMatch, &x6)));
    
    it2 = DLLGetPrev(DLLBegin(dll2));
    it2 = DLLSplice(it_start, it_end, it2);
    RUN_TEST(5 == DLLSize(dll2));
    RUN_TEST(0 == DLLSize(dll));
    it2 = DLLGetNext(it2);
    RUN_TEST(1 == *(int *)DLLGetData(it2));
    RUN_TEST(5 == *(int *)DLLGetData(DLLGetPrev(DLLEnd(dll2))));
    
    DLLDestroy(dll);
    DLLDestroy(dll2);
    
}

int main()
{
    TestCreateDLL();
 
    return 0;
}
