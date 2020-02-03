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
    trie_t *trie = TrieCreate(2);
    unsigned char ip1[4] = {255, 255, 255, 252};
    unsigned char ip2[4] = {255, 255, 255, 253};
    unsigned char ip3[4] = {255, 255, 255, 254};
    unsigned char ip4[4] = {255, 255, 255, 255};
    
    unsigned char next_available[4] = {0};
    
    printf("TrieTest1:\n");
    
    RUN_TEST(SUCCESS == TrieInsert(trie, ip1), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, ip2), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, ip3), "insert");
    RUN_TEST(SUCCESS == TrieInsert(trie, ip4), "insert");
    
    RUN_TEST(4 == TrieCountLeafs(trie), "countleafs");
    
    RUN_TEST(FALSE == TrieIsAvailable(trie, ip1), "isavailable");
    TrieFreeLeaf(trie, ip3);
    RUN_TEST(3 == TrieCountLeafs(trie), "countleafs");

    RUN_TEST(TRUE == TrieIsAvailable(trie, ip3), "isavailable");
    
    TrieNextAvailable(trie, next_available);
    
    TrieDestroy(trie);
    printf("\n\n");
}

int main()
{
    TrieTest1();
    
    return 0;
}
