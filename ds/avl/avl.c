/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   AVL Tree                    */
/*   Author: Yonatan Zaken       */
/*   Last Updated 16/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "avl.h"

#define LEFT 0
#define RIGHT 1

#define UNUSED(x) (void)(x)

typedef struct WrapperCompare
{
    compare_func_t cmp;
    void *user_data;
} isbefore_t;

struct AVLNode
{
	void *data;
	size_t height;
	struct AVLNode *child[NUM_OF_CHILDREN];
};

struct AVLTree
{
	isbefore_t isbefore;
	avl_node_t *root;
};

static int ChildSide(const void *wrapper, const void *tree_data)
{
    return (0 < ((isbefore_t*)wrapper)->cmp(((isbefore_t*)wrapper)->user_data, tree_data));
}

avl_t *AVLCreate(compare_func_t cmp)
{
    avl_t *avl = malloc(sizeof(*avl));
    if (NULL == avl)
    {
        return NULL;
    }
    avl->isbefore.cmp = cmp;
    avl->isbefore.user_data = NULL;
    avl->root = NULL;
    
    return avl;
}

static void RecDestroy(avl_node_t *node)
{
    if (NULL == node)
    {
        return;
    }
    
    RecDestroy(node->child[LEFT]);
    RecDestroy(node->child[RIGHT]);
    free(node); node = NULL;
    return;
}

void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);
    
    RecDestroy(tree->root);
    free(tree); tree = NULL;
}

static avl_node_t *CreateNode(void *data)
{    
    avl_node_t *node = malloc(sizeof(*node));
    if (NULL == node)
    {
        return NULL;
    }       
    
    node->data = data;
    node->height = 0;
    node->child[LEFT] = NULL;
    node->child[RIGHT] = NULL;
    
    return node;
}

static int RecInsert(isbefore_t isbefore, avl_node_t *node, void *data)
{
    if (NULL == node->child[ChildSide(&isbefore, node->data)])
    {
        if (NULL == (node->child[ChildSide(&isbefore, node->data)] =
                                               CreateNode(data)))
        {
            return 1;
        }
        return 0;
    }
    
    RecInsert(isbefore, node->child[ChildSide(&isbefore, node->data)], data);
}

int AVLInsert(avl_t *tree, void *data)
{    
    assert(NULL != tree);
    
    tree->isbefore.user_data = data;
    
    if (NULL == tree->root)
    {
        if (NULL == (tree->root = CreateNode(data)))
        {
            return 1;
        }
        return 0;        
    }
    
    return RecInsert(tree->isbefore, tree->root, data);
}

void AVLRemove(avl_t *tree, const void *data)
{

}

static void *RecFind(avl_node_t *node, isbefore_t isbefore)
{    
    if (NULL == node)
    {
        return NULL;
    }       
    
    else if (0 == isbefore.cmp(isbefore.user_data, node->data))
    {
        return node->data;
    }
    
    RecFind(node->child[ChildSide(&isbefore, node->data)], isbefore);
}

void *AVLFind(const avl_t *tree, const void *data)
{
    avl_t *avl = NULL;
    
    assert(NULL != tree);
    
    avl = (avl_t *)tree;   
    avl->isbefore.user_data = (void *)data;
    
    return (RecFind(tree->root, avl->isbefore));
}

static int RecForEach(avl_node_t *node, action_ptr_t action, void *param)
{
    int result = 1;
    
    if (NULL == node)
    {
        return result;
    }
    
    return (RecForEach(node->child[LEFT], action, param) + 
           action(node->data, param) + 
           RecForEach(node->child[RIGHT], action, param));
}

int AVLForeach(avl_t *tree, action_ptr_t action, void *param)
{
    assert(NULL != tree);
    
    return RecForEach(tree->root, action, param);
}

static size_t RecSize(avl_node_t *node)
{
    if (NULL == node)
    {
        return 0;
    }
    return (1 + RecSize(node->child[LEFT]) + RecSize(node->child[RIGHT]));
}

size_t AVLSize(const avl_t *tree)
{
    assert(NULL != tree);
    
    return RecSize(tree->root);
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);
    
    return (NULL == tree->root );
}

size_t GetHeight(const avl_t *tree)
{

}
