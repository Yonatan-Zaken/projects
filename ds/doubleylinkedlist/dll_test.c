/*********************************/
/*   			             	 */
/*   Main file DS 7              */
/*   Yonatan Zaken		         */
/*   Last Updated 7/12/19        */
/*   Reviewed by:            */   
/*			                   	 */
/*********************************/

#include <stdio.h>

#include "dllist.h"

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

struct DLLNode
{
    void *data;
    struct DLLNode *next;
    struct DLLNode *prev;
};

typedef struct DLLNode node_t;

struct Iterator
{
    struct DLLNode *node;
};

struct DLL
{
    struct DLLNode head;
    struct DLLNode tail;
};

static void TestDLL1()
{
    int data = 77;
    iterator_t it1;
    dll_t *dll1 = NULL;
    
    printf("DLL test 1:\n");
    
    dll1 = DLLCreate();
    it1.node = &dll1->tail;
   
    RUN_TEST(1 == DLLIsEmpty(dll1), "is empty test1");
    it1 = DLLInsert(dll1, it1, &data);
    RUN_TEST(1 == DLLSize(dll1), "size test1");
    RUN_TEST(0 == DLLIsEmpty(dll1), "is empty test1");
    it1 = DLLRemove(it1);
    RUN_TEST(1 == DLLIsEmpty(dll1), "is empty test1");
    it1 = DLLInsert(dll1, it1, &data);
    
    DLLDestroy(dll1);
    
    printf("\n");
}

int main()
{
    TestDLL1();
    
    return 0;
}
