/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   Binary Search Tree          */
/*   Author: Yonatan Zaken       */
/*   Last Updated 9/1/20         */
/*   Reviewed by: Eliya          */   
/*			                   	 */
/*********************************/
+
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "bst.h"

#define LEFT 0
#define RIGHT 1
#define DEADBEEF ((void *)0xDEADBEEF)

#define UNUSED(x) (void)(x)
#define FREE(ptr) {free(ptr); ptr = NULL;}

typedef struct BSTNode
{
    struct BSTNode *child[2];
    struct BSTNode *parent;
    void *node_data;
} bst_node_t;

struct BSTree
{
    bst_node_t dummy;
    compare_func_t cmp;
    void *param;
};

static int WhichChildSide(bst_itr_t it)
{
    assert(NULL != it);
    
    return (it == it->parent->child[RIGHT]);
}

bst_t *BSTCreate(compare_func_t cmp, void *param)
{
    bst_t *bst = (bst_t *)malloc(sizeof(bst_t));
    if (NULL == bst)
    {
        return NULL;
    }
    
    bst->dummy.child[LEFT] = NULL;
    bst->dummy.child[RIGHT] = NULL;
    bst->dummy.node_data = DEADBEEF;
    bst->cmp = cmp;
    bst->param = param;
    bst->dummy.parent = NULL;
    
    return bst;
}

void BSTDestroy(bst_t *tree)
{
    size_t bst_size = 0;
    
    assert(NULL != tree);
    
    bst_size = BSTSize(tree);
    
    while (0 < bst_size)
    {
        BSTRemove(tree->dummy.child[LEFT]);
        --bst_size;
    }
    FREE(tree);
}

static bst_node_t *CreateNode(bst_node_t *node, void *data)
{
    node = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (NULL == node)
    {
        return NULL;
    }
    
    node->child[LEFT] = NULL;
    node->child[RIGHT] = NULL;
    node->node_data = data;
    
    return node;
}

int BSTInsert(bst_t *tree, void *data)
{
    bst_node_t *runner = NULL;
    bst_node_t *it = NULL;
    int child_side = LEFT;
    
    assert(NULL != tree);
    
    it = CreateNode(it, data);
    if (NULL == it)
    {
        return 1;
    }
    
    runner = &tree->dummy;
    if (NULL == runner->child[LEFT])
    {
        runner->child[LEFT] = it;
        it->parent = runner;
        return 0; 
    }
    
    while (NULL != runner->child[child_side])
    {
        runner = runner->child[child_side];
        child_side = tree->cmp(data, runner->node_data, tree->param);
    }
    
    runner->child[child_side] = it;
    it->parent = runner;
    return 0;
}

void BSTRemove(bst_itr_t it)
{
    bst_itr_t successor;
    
    if (NULL == it->child[LEFT] && NULL == it->child[RIGHT])
    {
        it->parent->child[WhichChildSide(it)] = NULL;
    }
    
    else if (NULL != it->child[LEFT] && NULL != it->child[RIGHT])
    {
        successor = BSTNext(it);
        successor->parent->child[WhichChildSide(successor)] =
                                     successor->child[RIGHT];
                                     
        successor->child[RIGHT] = it->child[RIGHT];
        successor->child[LEFT] = it->child[LEFT];
        successor->parent = it->parent;
        it->parent->child[WhichChildSide(it)] = successor;
        
        if (NULL != successor->child[RIGHT])
        {
            successor->child[RIGHT]->parent = successor;
        }
        if (NULL != successor->child[LEFT])
        {
            successor->child[LEFT]->parent = successor;    
        }
    }
    
    else if (NULL == it->child[RIGHT])
    {
        it->parent->child[WhichChildSide(it)] = it->child[LEFT];
        it->child[LEFT]->parent = it->parent;
    }
    
    else
    {
        it->parent->child[WhichChildSide(it)] = it->child[RIGHT];
        it->child[RIGHT]->parent = it->parent;
    }
    
    FREE(it);
}

bst_itr_t BSTFind(const bst_t *tree, const void *data)
{
    int direction = 0;     
    bst_itr_t it = NULL;
    
    assert(NULL != tree);
    
    it = &((bst_t *)tree)->dummy;
     
    while (NULL != it->child[direction])
    {   
        it = it->child[direction];
        direction = tree->cmp(data, it->node_data, tree->param); 
    
        if ((0 == direction) && 
            (0 == tree->cmp(it->node_data, data, tree->param)))
        {
            return it;
        }
    }
    
    return BSTEnd(tree);
}

int BSTForeach(bst_itr_t start, bst_itr_t end, action_func_t action, void *param)
{
    int result = 0;
    bst_itr_t runner = start;
    
    assert(NULL != start);
    assert(NULL != end);            
        
    while ((0 == result) && !BSTIsSameItr(runner, end))
    {
        result = action(runner->node_data, param);
        runner = BSTNext(runner);
    }

    return result;
}

size_t BSTSize(const bst_t *tree)
{
    bst_itr_t it = NULL;
    bst_t *runner = NULL;
    size_t bst_size = 0;
     
    assert(NULL != tree);
    
    runner = (bst_t *)tree;
    it = BSTBegin(runner);
    
    while (DEADBEEF != it->node_data)
    {
        ++bst_size;
        it = BSTNext(it);
    }
    
    return bst_size;
}

int BSTIsEmpty(const bst_t *tree)
{
    assert (NULL != tree);
    
    return (NULL == tree->dummy.child[LEFT]);
}

void *BSTGetData(bst_itr_t it)
{   
    assert(NULL != it);
    
    return it->node_data;
}

bst_itr_t BSTBegin(const bst_t *tree)
{   
    bst_itr_t it = NULL;
     
    assert(NULL != tree);    
    
    it = &((bst_t *)tree)->dummy;
    
    while (NULL != it->child[LEFT])
    {
        it = it->child[LEFT];
    }
    
    return it;   
}

bst_itr_t BSTEnd(const bst_t *tree)
{
    assert(NULL != tree);
    
    return &(((bst_t *)tree)->dummy);           
}

bst_itr_t BSTNext(bst_itr_t it)
{
    if (NULL != it->child[RIGHT])
    {
        it = it->child[RIGHT];
        
        while (NULL != it->child[LEFT])
        {
            it = it->child[LEFT];
        }
        
        return it;
    }
       
    while (RIGHT == WhichChildSide(it))
    {
        it = it->parent;
    }
    
    return it->parent;
}

bst_itr_t BSTPrev(bst_itr_t it)
{
    if (NULL != it->child[LEFT])
    {
        it = it->child[LEFT];
        
        while (NULL != it->child[RIGHT])
        {
            it = it->child[RIGHT];
        }

        return it;
    }
            
    while ((LEFT == WhichChildSide(it)) && (DEADBEEF != it->parent->node_data))
    {
        it = it->parent;
    }
    
    return it->parent;
}

int BSTIsSameItr(bst_itr_t it1, bst_itr_t it2)
{
    assert(NULL != it1);
    assert(NULL != it2);
    
    return (it1 == it2);
}
