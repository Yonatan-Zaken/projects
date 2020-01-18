/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   AVL Tree                    */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/1/20        */
/*   Reviewed by:             */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */
#include <assert.h>

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
    
    RUN_TEST(2 == AVLGetHeight(tree), "get height1");
    
    AVLDestroy(tree);
    printf("\n\n");
}

int main()
{
    AvlTest1();   

    return 0;
}
