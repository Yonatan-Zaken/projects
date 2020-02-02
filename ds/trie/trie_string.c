/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Trie                        */
/*   Author: Yonatan Zaken       */
/*   Last Updated 30/1/20        */
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
    size_t height;
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

trie_t *TrieCreate(size_t height)
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
    
    trie->height = height;
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
    free(trie); trie = NULL;
}

static void UpdateAvailabilityIMP(trie_node_t *node)
{
    assert(NULL != node);
    
    if ((NULL != node->side[LEFT]) && (NULL != node->side[RIGHT]))
    {
        if ((OCCUPIED == node->side[LEFT]->availability) &&
            (OCCUPIED == node->side[RIGHT]->availability))
        {
            node->availability = OCCUPIED;            
        }    
    }
}

static status_t InsertIMP(trie_node_t *node, char *data)
{
    status_t status = 0;
    
    assert(NULL != node);
    
    if ('\0' == *data)
    {
        node->availability = OCCUPIED;
        return SUCCESS;
    }
    
    if (NULL == node->side[*data - ASCII_0])
    {
        
        if (NULL == (node->side[*data - ASCII_0] = CreateNode()))
        {
            return FAIL;
        }
    }
    ++data;
    status = InsertIMP(node->side[*(data - 1) - ASCII_0], data);
    
    UpdateAvailabilityIMP(node);
    
    return status;
    
}

status_t TrieInsert(trie_t *trie, char *data)
{
    assert(NULL != trie);
    
    return InsertIMP(trie->root, data);
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
    if (NULL == node)
    {
        return 0;
    }    
    
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

bool_t TrieIsExist(trie_t *trie, char *data)
{
    trie_node_t *node = NULL;
    char *runner = NULL;
    
    assert(NULL != node);
    assert(NULL != data);
    
    node = trie->root;
    runner = data;
    
    while ('\0' != *runner)
    {   
        if (NULL == (node = node->side[*runner - ASCII_0]))
        {
            return FALSE;        
        }
        ++runner;
    }
    
    return TRUE;
}

bool_t TrieIsAvailable(const trie_t *trie, char *data)
{
    trie_node_t *node = NULL;
    char *runner = NULL;
    
    assert(NULL != trie);
    assert(NULL != data);
    
    node = trie->root;    
    runner = data;
        
    while ('\0' != *runner)
    {
        if (OCCUPIED == node->availability)
        {
            return FALSE;
        }
        node = node->side[*runner - ASCII_0];
        ++runner;
    }
    
    return (VACANT == node->availability);
}

void TrieFreeLeaf(trie_t *trie, char *data)
{
    trie_node_t *node = NULL;
    char *runner = NULL;
    
    assert(NULL != trie);
    assert(NULL != data);
    
    node = trie->root;
    runner = data;
    
    while ('\0' != *runner)
    {
        node->availability = VACANT;
        node = node->side[*runner - ASCII_0];
        ++runner;
    }

    node->availability = VACANT;
}

static void CreatePath(char *buffer, size_t remaining_bits)
{
    char *runner = NULL;
    
    assert(NULL != buffer);
    
    runner = buffer;
    
    while (remaining_bits > 0)
    {
        *runner = '0';
        ++runner;
        --remaining_bits;
    }
}


char *TrieFirstAvailable(trie_t *trie, size_t available_bits, char *buffer)
{
    size_t i = 0;
    char *runner = NULL;
    size_t remaining_bits = available_bits;
    
    assert(NULL != trie);
    assert(NULL != data);
    
    runner = buffer;
    
    for (i = 0; i < available_bits; ++i)
    {
        if (NULL == node->side[LEFT])
        {
            CreatePath(buffer, remaining_bits);    
        }
        
        else if (VACANT == node->side[LEFT])
        {
            *buffer = '0';
            ++buffer;
        }
    }
    
}
