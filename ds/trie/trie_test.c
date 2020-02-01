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
    char *str1 = "00";
    char *str2 = "01";
    char *str3 = "10";
    char *str4 = "11";
    
    printf("TrieTest1:\n");
    
    RUN_TEST(SUCCESS == TrieInsert(trie, str1), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, str2), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, str3), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, str4), "insert");
    
    RUN_TEST(4 == TrieCountLeafs(trie), "countleafs");
    RUN_TEST(FALSE == TrieIsAvailable(trie, str1), "isavailable");
    TrieFreeLeaf(trie, str1);
    RUN_TEST(3 == TrieCountLeafs(trie), "countleafs");
    TrieFreeLeaf(trie, str3);
    RUN_TEST(2 == TrieCountLeafs(trie), "countleafs");
    RUN_TEST(TRUE == TrieIsAvailable(trie, str1), "isavailable");
    RUN_TEST(TRUE == TrieIsAvailable(trie, str3), "isavailable");
    
    
    TrieDestroy(trie);
    printf("\n\n");
}

int main()
{
    TrieTest1();
    
    return 0;
}
