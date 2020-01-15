/*********************************/
/*   			             	 */
/*   Header file DS 4            */
/*   Yonatan Zaken		         */
/*   Last Updated 3/12/19        */
/*   Reviewed by: shye           */   
/*			                   	 */
/*********************************/

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h> /* size_t */

typedef struct Node
{
    void *data;
    struct Node *next;
}node_t;

typedef int (*action_func_ptr)(void *node, void *additional);
typedef int (*match_func_ptr)(void *node, void *additional);

/* Creates a new node */
/* WARNING: Doesnt get NULL pointer */
node_t *LLCreateNode(node_t *next, const void *data);

/* Destroys the data structure */
/* WARNING: Doesnt get NULL pointer */
void LLDestroy(node_t *node);

/* Inserts a new node before the node sent to the function */
/* Returns 1 - no success inserting, 0 - success */
/* WARNING: Doesnt get NULL pointer */
int LLInsert(node_t *new_node, node_t *old_node);

/* Inserts a new node after the node sent to the function */
/* Returns 1 - no success inserting, 0 - success */
/* WARNING: Doesnt get NULL pointer */
int LLInsertAfter(node_t *new_node, node_t *previous_node);

/* Removes the node before the node sent to the function */
/* WARNING: Can't remove last  node */
/* WARNING: Doesnt get NULL pointer */
void LLRemove(node_t *node);

/* Removes the node after the node sent to the function */
/* WARNING: Doesnt get NULL pointer */
void LLRemoveAfter(node_t *node);

/* Returns a node according to a condition specified by the user */
/* WARNING: Doesnt get NULL pointer */
node_t *LLGetNode(const node_t *head, match_func_ptr, void *additional);

/* Performs a generic operation on all nodes in the data structure */
/* Returns 1 - no success performing for each node, 0 - success */
/* WARNING: Doesnt get NULL pointer */
int LLForEach(const node_t *head, action_func_ptr, void *additional);

/* Returns the number of nodes */
/* WARNING: Doesnt get NULL pointer */
size_t LLSize(const node_t *head);

/* Flips the direciton of pointing from last to first */
/* WARNING: Doesnt get NULL pointer */
node_t *LLFlip(node_t *head);

/* Checks if a loop occurs in the structure */
/* Returns 1 - loop occurs, 0 - loop doesnt occur */
/* WARNING: Doesnt get NULL pointer */
int LLHasLoop(const node_t *head);

/* Returns a pointer to the intersection node */
/* WARNING: Doesnt get NULL pointer */
node_t *LLFindIntersection(const node_t *head1, const node_t *head2);

#endif

