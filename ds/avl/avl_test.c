/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   AVL Tree                    */
/*   Author: Yonatan Zaken       */
/*   Last Updated 20/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "avl.h"

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

static int ActionFunc(void *tree_data, void *param)
{
    UNUSED(param);
    
    printf("%d \n", *(int*)tree_data);
    
    return 0;  
}

static int CompareFun(const void *user_data, const void *tree_data)
{
    return (*(int *)user_data - *(int *)tree_data);
}

static void AvlTest1()
{
    avl_t *tree = AVLCreate(&CompareFun);
    int x1 = 20, x2 = 10, x3 = 30, x4 = 3, x5 = 15, x6 = 25, x7 = 35, x8 = 40;
    
    printf("AVLTest 1:\n");
    RUN_TEST(1 == AVLIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == AVLInsert(tree, &x1), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x2), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x3), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x4), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x5), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x6), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x7), "insert1");
    
    RUN_TEST(7 == AVLSize(tree), "size1");
    RUN_TEST(NULL == AVLFind(tree, &x8), "find1");
    AVLForeach(tree, &ActionFunc, NULL);
    
    AVLRemove(tree, &x1);
    RUN_TEST(6 == AVLSize(tree), "size1");
    AVLForeach(tree, &ActionFunc, NULL);
    
    AVLRemove(tree, &x3);
    RUN_TEST(5 == AVLSize(tree), "size1");
    AVLForeach(tree, &ActionFunc, NULL);
    
    AVLRemove(tree, &x4);
    RUN_TEST(4 == AVLSize(tree), "size1");
    AVLForeach(tree, &ActionFunc, NULL);
    
    RUN_TEST(2 == AVLGetHeight(tree), "get height1");
    
    AVLDestroy(tree);
    printf("\n\n");
}

static void AvlTest2()
{
    avl_t *tree = AVLCreate(&CompareFun);
    int x1 = 30, x2 = 40, x3 = 20, x4 = 10, x5 = 5;
    
    printf("AVLTest 1:\n");
    RUN_TEST(1 == AVLIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == AVLInsert(tree, &x1), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x2), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x3), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x4), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x5), "insert1");
    
    RUN_TEST(5 == AVLSize(tree), "size1");
        
    RUN_TEST(2 == AVLGetHeight(tree), "get height1");
    
    AVLDestroy(tree);
    printf("\n\n");
}

static void AvlTest3()
{
    avl_t *tree = AVLCreate(&CompareFun);
    int x1 = 30, x2 = 40, x3 = 20, x4 = 10;
    
    printf("AVLTest 1:\n");
    RUN_TEST(1 == AVLIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == AVLInsert(tree, &x1), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x2), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x3), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x4), "insert1");
    RUN_TEST(4 == AVLSize(tree), "size1");
    
    AVLRemove(tree, &x2);
    RUN_TEST(3 == AVLSize(tree), "size1");
    AVLForeach(tree, &ActionFunc, NULL);
    
    AVLDestroy(tree);
    printf("\n\n");
}

static void AvlTest4()
{
    avl_t *tree = AVLCreate(&CompareFun);
    int x1 = 20, x2 = 10, x3 = 30, x4 = 3, x5 = 15, x6 = 25, x7 = 35,
    x8 = 1, x9 = 5, x10 = 12, x11 = 17, x12 = 23, x13 = 27, x14 = 33, x15 = 38,
    x16 = 24;
    
    printf("AVLTest 1:\n");
    RUN_TEST(1 == AVLIsEmpty(tree), "is empty1");
    
    RUN_TEST(0 == AVLInsert(tree, &x1), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x2), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x3), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x4), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x5), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x6), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x7), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x8), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x9), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x10), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x11), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x12), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x13), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x14), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x15), "insert1");
    RUN_TEST(0 == AVLInsert(tree, &x16), "insert1");
    RUN_TEST(16 == AVLSize(tree), "size1");
    AVLForeach(tree, &ActionFunc, NULL);
    
    AVLRemove(tree, &x1);
    RUN_TEST(15 == AVLSize(tree), "size1");
    AVLForeach(tree, &ActionFunc, NULL);

    
    RUN_TEST(3 == AVLGetHeight(tree), "get height1");
    
    AVLDestroy(tree);
    printf("\n\n");
}

int main()
{
    AvlTest1();
    AvlTest2();   
    AvlTest3();
    AvlTest4();
    
    
    return 0;
}
