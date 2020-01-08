/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Binary Search Tree          */
/*   Author: Yonatan Zaken       */
/*   Last Updated 7/1/20         */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */
#include <assert.h>

#include "bst.h"

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

typedef struct BSTNode
{
    struct BSTNode *child[2];
    struct BSTNode *parent;
    void *node_data;
} bst_node_t;

struct BSTree
{
    bst_node_t dummy;
    compare_func_t cmp;
    void *param;
};

static int CompareFunc(const void *user_data, const void *tree_data, void *param)
{
    return (*(int *)user_data > *(int *)tree_data);
}

static int ActionFunc(const void *user_data, const void *tree_data, void *param)
{
    *(int *)tree_data += 1;
    return 
}

static void BSTTest1()
{
    void *param = NULL;
    bst_t *tree = BSTCreate(&CompareFunc, param);
    int x1 = 20, x2 = 10, x3 = 30, x4 = 3, x5 = 15, x6 = 25, x7 = 35;
    bst_itr_t it1, it2, it3;
    
    printf("BSTTest 1:\n");
    RUN_TEST(1 == BSTIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == BSTInsert(tree, &x1), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x2), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x3), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x4), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x5), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x6), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x7), "insert1");
    
    RUN_TEST(7 == BSTSize(tree), "size1");
    
    it1 = tree->dummy.child[0];
    
    it1 = BSTNext(it1);
    RUN_TEST(25 == *(int *)(it1->node_data), "next1");
    it1 = BSTPrev(it1);
    RUN_TEST(20 == *(int *)(it1->node_data), "next1");
    it3 = it1;
    it1 = BSTPrev(it1);
    it1 = BSTPrev(it1);
    it2 = it1;
    it1 = BSTPrev(it1);
    RUN_TEST(3 == *(int *)(it1->node_data), "next1");
    
    BSTRemove(it1);
    RUN_TEST(NULL == it2->child[0], "remove1");
    BSTRemove(it2);
    RUN_TEST(15 == *(int*)(it3->child[0]->node_data), "remove1");
    BSTRemove(it3);
    RUN_TEST(25 == *(int*)(tree->dummy.child[0]->node_data), "remove1");
    BSTDestroy(tree);
    
    printf("\n\n");
}

static void BSTTest2()
{
    void *param = NULL;
    bst_t *tree = BSTCreate(&CompareFunc, param);
    int x1 = 20, x2 = 10, x3 = 30, x4 = 3, x5 = 15, x6 = 25, x7 = 35;
    bst_itr_t it1, it2, it3;
    
    printf("BSTTest 2:\n");
    RUN_TEST(1 == BSTIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == BSTInsert(tree, &x1), "insert2");
    RUN_TEST(0 == BSTInsert(tree, &x2), "insert2");
    RUN_TEST(0 == BSTInsert(tree, &x3), "insert2");
    RUN_TEST(0 == BSTInsert(tree, &x4), "insert2");
    RUN_TEST(0 == BSTInsert(tree, &x5), "insert2");
    RUN_TEST(0 == BSTInsert(tree, &x6), "insert2");
    RUN_TEST(0 == BSTInsert(tree, &x7), "insert2");
    
    RUN_TEST(7 == BSTSize(tree), "size2");
    it1 = tree->dummy.child[0];
    it2 = it1;
    it1 = BSTPrev(it1);
    it1 = BSTPrev(it1);
    
    RUN_TEST(3 == *(int*)((BSTBegin(tree))->node_data), "begin1");
    BSTRemove(BSTBegin(tree));
    
    RUN_TEST(10 == *(int*)((BSTBegin(tree))->node_data), "begin1");
    BSTRemove(BSTBegin(tree));

    RUN_TEST(15 == *(int*)((BSTBegin(tree))->node_data), "begin1");  
    
    RUN_TEST(35 == *(int*)(BSTEnd(tree))->node_data, "end1");
    BSTRemove(BSTEnd(tree));
    
    RUN_TEST(30 == *(int*)(BSTEnd(tree))->node_data, "end1");
    BSTRemove(it2);
    
    RUN_TEST(30 == *(int*)(BSTEnd(tree))->node_data, "end1");
    RUN_TEST(15 == *(int*)(BSTBegin(tree))->node_data, "end1");
    BSTDestroy(tree);
    
    printf("\n\n");  
}

static void BSTTest3()
{
    void *param = NULL;
    bst_t *tree = BSTCreate(&CompareFunc, param);
    int x1 = 20, x2 = 10, x3 = 30, x4 = 3, x5 = 15, x6 = 25, x7 = 35;
    bst_itr_t it1, it2, it3;
    
    printf("BSTTest 3:\n");
    RUN_TEST(1 == BSTIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == BSTInsert(tree, &x1), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x2), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x3), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x4), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x5), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x6), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x7), "insert1");
    
    RUN_TEST(7 == BSTSize(tree), "size1");
    
    it1 = tree->dummy.child[0];
    
    BSTDestroy(tree);
    
    printf("\n\n");
}

static void BSTTest4()
{
    void *param = NULL;
    bst_t *tree = BSTCreate(&CompareFunc, param);
    int x1 = 20, x2 = 10, x3 = 30, x4 = 3, x5 = 15, x6 = 25, x7 = 35, x8 = 99;
    bst_itr_t it1, it2, it3;
    
    printf("BSTTest 4:\n");
    RUN_TEST(1 == BSTIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == BSTInsert(tree, &x1), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x2), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x3), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x4), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x5), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x6), "insert1");
    RUN_TEST(0 == BSTInsert(tree, &x7), "insert1");
    
    RUN_TEST(7 == BSTSize(tree), "size1");
    
    it1 = tree->dummy.child[0];
    
    RUN_TEST(15 == *(int*)BSTGetData(BSTFind(tree, &x5)), "find4");
    RUN_TEST(25 == *(int*)BSTGetData(BSTFind(tree, &x6)), "find4");
    RUN_TEST((void*)0xDEADBEEF == BSTGetData(BSTFind(tree, &x8)), "find4");
    
        
    BSTDestroy(tree);
    
    printf("\n\n");
}

int main()
{
    BSTTest1();
    /*BSTTest2();*/
    BSTTest3();
    BSTTest4();
    
    return 0;
}






