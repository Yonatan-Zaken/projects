/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Trie                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 30/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "trie.h"

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

static void TrieTest1()
{
    trie_t *trie = TrieCreate();
    char *str1 = "1001";
    char *str2 = "1110";
    char *str3 = "0001";
    
    printf("TrieTest1:\n");
    
    RUN_TEST(SUCCESS == TrieInsert(trie, str1), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, str2), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, str3), "insert");
    RUN_TEST(3 == TrieCountLeafs(trie), "countleafs");
    RUN_TEST(1 == TrieIsAvailable(trie, str1), "isavailable");
    
    TrieDestroy(trie);
    printf("\n\n");
}

int main()
{
    TrieTest1();
    
    return 0;
}
