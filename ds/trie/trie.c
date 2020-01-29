/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Trie                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 29/1/20        */
/*   Reviewed by:          */   
/*			                   	 */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "trie.h"

#define ASCII_0 48

typedef enum ChildSide
{
    LEFT,
    RIGHT,
    NUM_OF_CHILD
} side_t;

typedef enum Availability
{
    VACANT,
    OCCUPIED
} availability_t;

typedef struct TrieNode
{
    struct TrieNode *side[NUM_OF_CHILD];
    availability_t availability;
} trie_node_t;

struct Trie
{
    trie_node_t *root;
};

static trie_node_t *CreateNode()
{
    trie_node_t *node = malloc(sizeof(*node));
    if (NULL != node)
    {
        node->side[LEFT] = NULL;
        node->side[RIGHT] = NULL;
        node->availability = VACANT;
        return node;
    }
    
    return NULL;
}

trie_t *TrieCreate()
{
    trie_t *trie = malloc(sizeof(*trie));
    if (NULL != trie)
    {
        trie->root = CreateNode();
        if (NULL == trie->root)
        {
            free(trie); trie = NULL;
            return NULL;
        }
    }
    
    return trie; 
}

static void DestroyIMP(trie_node_t *node)
{
    if (NULL == node)
    {
        return;
    }
    
    DestroyIMP(node->side[LEFT]);
    DestroyIMP(node->side[RIGHT]);
    free(node); node = NULL;

    return;
}

void TrieDestroy(trie_t *trie)
{    
    assert(NULL != trie);
     
    DestroyIMP(trie->root);
}

status_t TrieInsert(trie_t *trie, char *data)
{
    size_t side = 0;
    char *runner = NULL;
    trie_node_t *node = NULL;
    
    assert(NULL != trie);
    assert(NULL != data);
    
    runner = data;
    node = trie->root;
    
    while (('\0' != *runner) && (VACANT == node->availability))
    {
        side = *runner - ASCII_0;
        if (NULL == node->side[side])
        {
            node->side[side] = CreateNode();
            if (NULL == node->side[side])
            {
                return FAIL;
            }    
        }
        
        node = node->side[side];
        ++runner; 
    }
    
    node->availability = OCCUPIED;
    return SUCCESS;    
}

bool_t TrieIsEmpty(const trie_t *trie)
{
    return ((NULL == trie->root->side[LEFT]) && (NULL == trie->root->side[RIGHT]));
}

static size_t SizeIMP(trie_node_t *node)
{
    if (NULL == node)
    {
        return 0;
    }
    
    return (1 + SizeIMP(node->side[LEFT]) + SizeIMP(node->side[RIGHT]));
}

size_t TrieSize(const trie_t *trie)
{
    assert(NULL != trie);
    
    return SizeIMP(trie->root);
}

static size_t CountLeafsIMP(trie_node_t *node)
{
    if ((NULL == node->side[LEFT])  &&
        (NULL == node->side[RIGHT]) && node->availability == OCCUPIED)
    {
        return 1;
    }
    
    return (CountLeafsIMP(node->side[LEFT]) + CountLeafsIMP(node->side[RIGHT]));
}

size_t TrieCountLeafs(const trie_t *trie)
{
    assert(NULL != trie);
    
    return CountLeafsIMP(trie->root);
}

bool_t TrieIsExist(const trie_t *trie, char *data)
{
    char *runner = NULL;
    trie_node_t *node = NULL;
    
    assert(NULL != trie);
    assert(NULL != data);
    
    node = trie->root;
    runner = data;
    
    while ('\0' != *runner)
    {
        node = node->side[*runner - ASCII_0];
        if (NULL == node)
        {
            return FALSE;
        }
        
        ++runner;
    }
    
    return (OCCUPIED == node->availability);
}

