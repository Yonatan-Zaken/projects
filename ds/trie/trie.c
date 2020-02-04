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
#include <string.h> /* memcpy */

#include "trie.h"

#define MASK 0x01U
#define BITS_IN_BYTE 8
#define BITS_IN_IP 32
#define ADDRESS_SIZE_IN_BYTES 4

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

static unsigned char SideFinderIMP(unsigned char *data, size_t height)
{
    unsigned char shift_holder = (height - 1) % BITS_IN_BYTE;
    unsigned char result = 0;
    
    assert(NULL != data);
    
    result = (*(data + (BITS_IN_IP - height) / BITS_IN_BYTE) &
             (MASK << ((height - 1) % BITS_IN_BYTE)));
        
    return (result >> shift_holder);
}

static status_t InsertIMP(trie_node_t *node, unsigned char *data, size_t height)
{
    unsigned char side = 0;
    status_t status = 0;
    
    assert(NULL != node);
    
    side = SideFinderIMP(data, height);
    
    if (0 == height)
    {
        node->availability = OCCUPIED;
        return SUCCESS;
    }
    
    if (NULL == node->side[side])
    {     
        if (NULL == (node->side[side] = CreateNode()))
        {
            return FAIL;
        }
    }
    --height;
    status = InsertIMP(node->side[side], data, height);
    UpdateAvailabilityIMP(node);
    
    return status;
}

status_t TrieInsert(trie_t *trie, unsigned char *data)
{
    assert(NULL != trie);
    assert(NULL != data);
    
    return InsertIMP(trie->root, data, trie->height);
}

bool_t TrieIsEmpty(const trie_t *trie)
{
    return ((NULL == trie->root->side[LEFT]) && (NULL == trie->root->side[RIGHT]));
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

bool_t TrieIsAvailable(const trie_t *trie, unsigned char *data)
{
    trie_node_t *node = NULL;
    size_t height = 0;
    
    assert(NULL != trie);
    assert(NULL != data);
    
    node = trie->root;    
    height = trie->height;
    
    while ((0 < height) && (NULL != node->side[SideFinderIMP(data, height)]))
    {
        node = node->side[SideFinderIMP(data, height)]; 
        --height;
    }
    
    return (VACANT == node->availability);
}

void TrieFreeLeaf(trie_t *trie, unsigned char *data)
{
    trie_node_t *node = NULL;
    size_t height = 0;
    
    assert(NULL != trie);
    assert(NULL != data);
    
    node = trie->root;
    height = trie->height;
    
    while ((0 < height) && (NULL != node))
    {
        node->availability = VACANT;
        node = node->side[SideFinderIMP(data, height)];
        --height;
    }
    
    if (NULL == node)
    {
        return;
    }
    node->availability = VACANT;
}

static void NextAvailableIMP(trie_node_t *node, size_t height, unsigned char *buffer) 
{
    if ((NULL == node) || (0 == height))
    {
        return;  
    }
    
    if (VACANT == node->side[LEFT]->availability)
    {
        NextAvailableIMP(node->side[LEFT], --height, buffer); 
    }
    
    else
    {
        *(buffer + (BITS_IN_IP - height) / BITS_IN_BYTE) |= 
                     (MASK << (height - 1) % BITS_IN_BYTE);           
        NextAvailableIMP(node->side[RIGHT], --height, buffer);
    } 
}

void TrieNextAvailable(trie_t *trie, unsigned char *ip_allocated)
{  
    assert(NULL != trie);
    
    NextAvailableIMP(trie->root, trie->height, ip_allocated);
}
