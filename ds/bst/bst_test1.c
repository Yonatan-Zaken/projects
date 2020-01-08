/*********************************/
/*    Data Structures            */
/*    Binary Search Tree         */       
/*    Author: Guy Cohen Zedek    */
/*    Date:   8/01/2020          */
/*                               */
/*********************************/
#include <stdio.h>

#include "bst.h"

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

static int Compare(const void *user_data, const void *data, void *param)
{
    UNUSED(param);
    
    return ((*(int *)(user_data)) > (*(int *)(data)));
}

static int AddNum(void *node_data, void *num)
{
    *(int *)node_data += *(int *)num;
    
    return 0;
}

static int PrintTree(void *node_data, void *param)
{
    UNUSED(param);
    
    printf("%d\n", *(int *)node_data);
    
    return 0;
}

static void TestCreate()
{
    bst_t *tree = BSTCreate(&Compare, NULL);
    
    printf("Create:\n");
    RUN_TEST(0 == BSTSize(tree));
    RUN_TEST(1 == BSTIsEmpty(tree));
    
    BSTDestroy(tree); tree = NULL;   
}

static void TestInsert()
{
    bst_t *tree = BSTCreate(&Compare, NULL);
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    
    printf("\nInsert:\n");
    RUN_TEST(0 == BSTSize(tree));
    RUN_TEST(1 == BSTIsEmpty(tree));
    
    RUN_TEST(0 == BSTInsert(tree, &x4));
    RUN_TEST(0 == BSTInsert(tree, &x5));
    RUN_TEST(0 == BSTInsert(tree, &x3));
    RUN_TEST(0 == BSTInsert(tree, &x1));
    RUN_TEST(0 == BSTInsert(tree, &x2));
    RUN_TEST(0 == BSTInsert(tree, &x6));
    RUN_TEST(0 == BSTInsert(tree, &x7));
    
    RUN_TEST(7 == BSTSize(tree));
    
    BSTDestroy(tree); tree = NULL; 
}

static void TestRemove()
{
    bst_t *tree = BSTCreate(&Compare, NULL);
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    bst_itr_t it1 = NULL;
    
    printf("\nRemove:\n");
    RUN_TEST(0 == BSTSize(tree));
    RUN_TEST(1 == BSTIsEmpty(tree));
    
    RUN_TEST(0 == BSTInsert(tree, &x4));
    RUN_TEST(0 == BSTInsert(tree, &x5));
    RUN_TEST(0 == BSTInsert(tree, &x3));
    RUN_TEST(0 == BSTInsert(tree, &x1));
    RUN_TEST(0 == BSTInsert(tree, &x2));
    RUN_TEST(0 == BSTInsert(tree, &x6));
    RUN_TEST(0 == BSTInsert(tree, &x7));
    
    RUN_TEST(7 == BSTSize(tree));
    
    it1 = BSTBegin(tree);
    RUN_TEST(1 == *(int *)BSTGetData(it1));
    
    it1 = BSTNext(it1);
    it1 = BSTNext(it1);
    it1 = BSTNext(it1);
    
    RUN_TEST(4 == *(int *)BSTGetData(it1));
    
    it1 = BSTPrev(it1);
    it1 = BSTPrev(it1);
    
    RUN_TEST(2 == *(int *)BSTGetData(it1)); 
    
    it1 = BSTPrev(it1);
    BSTRemove(it1);
    
    RUN_TEST(6 == BSTSize(tree));
    
    it1 = BSTBegin(tree);
    RUN_TEST(2 == *(int *)BSTGetData(it1));
    
    
    BSTDestroy(tree); tree = NULL; 
}

static void TestRemove2()
{
    bst_t *tree = BSTCreate(&Compare, NULL);
    int x1 = 1, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    bst_itr_t it1 = NULL;
    
    printf("\nRemove 2:\n");
    RUN_TEST(0 == BSTSize(tree));
    RUN_TEST(1 == BSTIsEmpty(tree));
    
    RUN_TEST(0 == BSTInsert(tree, &x4));
    RUN_TEST(0 == BSTInsert(tree, &x1));
    RUN_TEST(0 == BSTInsert(tree, &x6));
    RUN_TEST(0 == BSTInsert(tree, &x5));
    RUN_TEST(0 == BSTInsert(tree, &x7));
    
    RUN_TEST(5 == BSTSize(tree));
    
    it1 = BSTBegin(tree);
    RUN_TEST(1 == *(int *)BSTGetData(it1));
    
    it1 = BSTNext(it1);
    BSTRemove(it1);
    
    it1 = BSTBegin(tree);
    RUN_TEST(1 == *(int *)BSTGetData(it1));
    
    it1 = BSTNext(it1);
    RUN_TEST(5 == *(int *)BSTGetData(it1));
    
    BSTDestroy(tree); tree = NULL; 
}

static void TestFind()
{
    bst_t *tree = BSTCreate(&Compare, NULL);
    int x1 = 1, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    bst_itr_t it1 = NULL;
    
    printf("\nFind:\n");
    RUN_TEST(0 == BSTSize(tree));
    RUN_TEST(1 == BSTIsEmpty(tree));
    
    RUN_TEST(0 == BSTInsert(tree, &x4));
    RUN_TEST(0 == BSTInsert(tree, &x1));
    RUN_TEST(0 == BSTInsert(tree, &x6));
    RUN_TEST(0 == BSTInsert(tree, &x5));
    RUN_TEST(0 == BSTInsert(tree, &x7));
    
    RUN_TEST(5 == BSTSize(tree));
    
    it1 = BSTFind(tree, &x3);
    
    RUN_TEST(1 == BSTIsSameItr(it1, BSTEnd(tree)));
    
    it1 = BSTFind(tree, &x5);
    
    RUN_TEST(5 == *(int *)BSTGetData(it1));
    
    printf("Before Add Number:\n");

   /* RUN_TEST(0 == BSTForeach(BSTBegin(tree), BSTEnd(tree), &PrintTree, NULL));
    
    RUN_TEST(0 == BSTForeach(BSTBegin(tree), BSTEnd(tree), &AddNum, &x3));

    printf("After Add Number:\n");
    
    RUN_TEST(0 == BSTForeach(BSTBegin(tree), BSTEnd(tree), &PrintTree, NULL));
*/
    BSTDestroy(tree); tree = NULL; 
}

int main()
{
    TestCreate();
    TestInsert();
    TestRemove();
    TestRemove2();
    TestFind();
    
    return 0;
}
