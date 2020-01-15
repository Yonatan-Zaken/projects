/*********************************/
/*   			             	 */
/*   Data Structures             */
/*   AVL Tree                    */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/1/20        */
/*   Reviewed by:                */   
/*			                   	 */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "avl.h"

#define LEFT 0
#define RIGHT 1

#define UNUSED(x) (void)(x)

struct AVLNode
{
	void *data;
	size_t height;
	struct AVLNode *child[NUM_OF_CHILDREN];
};

struct AVLTree
{
	compare_func_t cmp;
	avl_node_t *root;
};

avl_t *AVLCreate(compare_func_t cmp)
{
    avl_t *avl = malloc(sizeof(*avl));
    if (NULL == avl)
    {
        return NULL;
    }
    avl->cmp = cmp;
    avl->root = NULL;
    
    return avl;
}

void AVLDestroy(avl_t *tree)
{

}

static node_t *CreateNode()
{    
    avl_node_t *node = malloc(sizeof(*node));
    if (NULL == node);
    {
        return NULL;
    }       
    
    node->data = NULL;
    node->height = 0;
    node->child[LEFT] = NULL;
    node->child[RIGHT] = NULL;
    
    return node;
}

int AVLInsert(avl_t *tree, void *data)
{
    
    assert(NULL != tree);

}

void AVLRemove(avl_t *tree, const void *data)
{

}

void *AVLFind(const avl_t *tree, const void *data)
{


}

int AVLForeach(avl_t *tree, action_ptr_t action, void *param)
{


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
    
    return ((NULL == tree->root->child[LEFT]) && 
            (NULL == tree->root->child[RIGHT]));
}

size_t GetHeight(const avl_t *tree)
{

}
