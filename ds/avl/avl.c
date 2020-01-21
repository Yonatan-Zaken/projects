/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   AVL Tree                    */
/*   Author: Yonatan Zaken       */
/*   Last Updated 20/1/20        */
/*   Reviewed by: Israel         */   
/*			                   	 */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "avl.h"

#define LEFT 0
#define RIGHT 1

#define MaxSubtree(a, b) ((a > b) ? a : b) 

enum
{
	LEFT_CHILD,
	RIGHT_CHILD,
	NUM_OF_CHILDREN
};

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

static int ChildSide(const void *isbefore, const void *tree_data)
{
    return (0 < ((isbefore_t*)isbefore)->cmp(((isbefore_t*)isbefore)->user_data, tree_data));
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

static void UpdateHeight(avl_node_t *node)
{
    long left_height = -1;
    long right_height = -1;
    
    if (NULL == node)
    {
        return;
    }
    
    if (NULL != node->child[LEFT])
    {
        left_height = node->child[LEFT]->height; 
    }

    if (NULL != node->child[RIGHT])
    {
        right_height = node->child[RIGHT]->height;
    }
    
    node->height = (1 + MaxSubtree(left_height, right_height));  
}

static avl_node_t *Rotate(avl_node_t *node, int side)
{
    avl_node_t *holder = node->child[side];
    node->child[side] = holder->child[!side];
    holder->child[!side] = node;
    UpdateHeight(node);
    UpdateHeight(holder);
    
    return holder;    
}

static int Height(avl_node_t *node)
{
    if (NULL == node)
    {
        return -1;
    }
    
    return node->height;
}

static int BalanceFactor(avl_node_t *node)
{
    if (NULL == node)
    {
        return -1;
    }
    return (Height(node->child[LEFT]) - Height(node->child[RIGHT]));
}

static avl_node_t* BalanceTree(avl_node_t *node)
{
    int b_factor = BalanceFactor(node);
    
    if (2 <= b_factor)
    {
        if (-1 >= BalanceFactor(node->child[LEFT]))
        {
            node->child[LEFT] = Rotate(node->child[LEFT], RIGHT);
        }
        
        node = Rotate(node, LEFT);
    }
    
    if (-2 >= b_factor)
    {
        if (1 <= BalanceFactor(node->child[RIGHT]))
        {
            node->child[RIGHT] = Rotate(node->child[RIGHT], LEFT);
        }
        node = Rotate(node, RIGHT);   
    }
    
    return node;
}

static avl_node_t *RecInsert(isbefore_t isbefore, avl_node_t *node, void *data)
{
    size_t side = ChildSide(&isbefore, node->data);
    if (NULL == node->child[side])
    {
        if (NULL == (node->child[side] = CreateNode(data)))
        {
            return NULL;
        }
        UpdateHeight(node);
        return node;
    }
    
    node->child[side] = RecInsert(isbefore, node->child[side], data);
    UpdateHeight(node);
    return BalanceTree(node);
}

int AVLInsert(avl_t *tree, void *data)
{    
    assert(NULL != tree);
    
    tree->isbefore.user_data = data;
    
    if (NULL == tree->root)
    {
        return (NULL == (tree->root = CreateNode(data)));
    }
    
    return (NULL == (tree->root = RecInsert(tree->isbefore, tree->root, data)));
}

static avl_node_t *TwoChildSucc(avl_node_t *node)
{
    avl_node_t *successor = NULL;
    if (NULL == node->child[LEFT])
    {
        return node;
    }
    
    else if (NULL == node->child[LEFT]->child[LEFT])
    {
        successor = node->child[LEFT]; 
        node->child[LEFT] = node->child[LEFT]->child[RIGHT];
        UpdateHeight(node->child[LEFT]);
        UpdateHeight(node);
        return successor;
    }
    
    successor = TwoChildSucc(node->child[LEFT]);
    UpdateHeight(node);
    return successor;
}

static avl_node_t *FindSuccessor(avl_node_t *node)
{
    avl_node_t *successor = NULL;
    
    if (NULL != node->child[LEFT])
    {
        if (NULL != node->child[RIGHT])
        {
            successor = TwoChildSucc(node->child[RIGHT]);
            if (node->child[RIGHT] != successor)
            {
                successor->child[RIGHT] = node->child[RIGHT];    
            }
            successor->child[LEFT] = node->child[LEFT];
            UpdateHeight(successor);
            return BalanceTree(successor);
        }   
        return node->child[LEFT];
    }
    return node->child[RIGHT];
}

static avl_node_t *RecRemove(avl_node_t *node, isbefore_t isbefore)
{
    avl_node_t *new_child = NULL;
    
    if (NULL == node)
    {
        return NULL;
    }
    
    else if (0 == isbefore.cmp(isbefore.user_data, node->data))
    {
        new_child = FindSuccessor(node);
        UpdateHeight(new_child);
        free(node); node = NULL;
        return BalanceTree(new_child);
    }
    
    node->child[ChildSide(&isbefore, node->data)] = 
    RecRemove(node->child[ChildSide(&isbefore, node->data)], isbefore);
    
    UpdateHeight(node);
    return BalanceTree(node);
}

void AVLRemove(avl_t *tree, const void *data)
{
    assert(NULL != tree);
    
    tree->isbefore.user_data = (void *)data;
    tree->root = RecRemove(tree->root, tree->isbefore);
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
    
    return RecFind(node->child[ChildSide(&isbefore, node->data)], isbefore);
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
    if (NULL == node)
    {
        return 0;
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

size_t AVLGetHeight(const avl_t *tree)
{
    assert(NULL != tree);
    
    return (tree->root->height);
}
