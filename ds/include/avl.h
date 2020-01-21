#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stddef.h> /* size_t */

typedef struct AVLTree avl_t;
typedef struct AVLNode avl_node_t;

/*********************************************** 
    Returns a 0 for equalization, 1 for user > tree 
	-1 for tree > data    
 ***********************************************/
typedef int (*compare_func_t)(const void *user_data, const void *tree_data);
typedef int (*action_ptr_t)(void *tree_data, void *param);

/*********************************************** 
    Returns a pointer to the AVL data structure
	Complexity of malloc     
 ***********************************************/
avl_t *AVLCreate(compare_func_t cmp);

/************************************************** 
	Destroys the AVL data and free it from memory 
	Complexity o(n) * free                            
 **************************************************/
void AVLDestroy(avl_t *tree);

/********************************************************************* 
	Gets a pointer to the tree and insert new data in the correct place  
	Return 0 for success, otherwise: 1
	Complexity of malloc * O(log(n))                            
 ********************************************************************/
int AVLInsert(avl_t *tree, void *data);

/*********************************************** 
	Get a pointer to data to remove from the tree
	Complexity: O(log n)
 ***********************************************/
void AVLRemove(avl_t *tree, const void *data);

/*********************************************************************** 
	Gets a pointer to the tree and search if the data exist in the tree
	Returns the data if it was found, otherwise: NULL
	Complexity: avg-case: O(log(n)), worst-case: O(log(n))
 ***********************************************************************/
void *AVLFind(const avl_t *tree, const void *data);

/********************************************************************************** 
	Gets a tree pointer and action function pointer to operate on the elements in the tree
	Returns 0 for success, otherwise: non-zero value
	Complexity: worst-case: O(n) 
 ***********************************************************************************/
int AVLForeach(avl_t *tree, action_ptr_t action, void *param);

/*********************************************** 
	Gets a pointer to the tree
	Returns the size of the tree
	complexity: O(n)                  
 ***********************************************/
size_t AVLSize(const avl_t *tree);

/*********************************************** 
	Gets a pointer to the tree
	Returns 1 if empty, otherwise: 0
	Complexity: O(1)
 ***********************************************/
int AVLIsEmpty(const avl_t *tree);

size_t AVLGetHeight(const avl_t *tree);

#endif
