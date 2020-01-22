/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Hash Table                  */
/*   Author: Yonatan Zaken       */
/*   Last Updated 20/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "hash.h"

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

static int ActionFunc(void *node_data, void *param)
{
    UNUSED(param);
    
    printf("%d \n", *(int*)node_data);
    
    return 0;  
}

static int MatchFunc(void *user_data, void *node_data)
{
    return (*(int*)user_data == *(int*)node_data);
}

static size_t HashFunc(const void *data)
{
    return (*(int*)data % 40);
}

static void HashTest1()
{
    hash_t *hash = HashCreate(2, &HashFunc, &MatchFunc);
    int x1 = 11, x2 = 10, x3 = 22, x4 = 7, x5 = 25, x6 = 33, x7 = 100;
    
    printf("HashTest1: \n"); 
    
    RUN_TEST(1 == HashIsEmpty(hash), "isempty1");
       
    RUN_TEST(0 == HashInsert(hash, &x1), "insert1");
    RUN_TEST(0 == HashInsert(hash, &x2), "insert1");
    RUN_TEST(0 == HashInsert(hash, &x3), "insert1");
    RUN_TEST(0 == HashInsert(hash, &x4), "insert1");
    RUN_TEST(0 == HashInsert(hash, &x5), "insert1");
    RUN_TEST(0 == HashInsert(hash, &x6), "insert1");
    RUN_TEST(6 == HashSize(hash), "size1");
    
    HashRemove(hash, &x2);
    RUN_TEST(5 == HashSize(hash), "size1");
    
    RUN_TEST(33 == *(int*)HashFind(hash, &x6), "find1");
    RUN_TEST(11 == *(int*)HashFind(hash, &x1), "find1");
    RUN_TEST(NULL == HashFind(hash, &x7), "find1");
    
    HashForeach(hash, &ActionFunc, NULL);
    
    HashDestroy(hash);
    
    printf("\n\n");
}

int main()
{
    HashTest1();
    return 0;
}
