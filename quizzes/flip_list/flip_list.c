/*
* Flip the direction of a linked list
*/
#include <stdio.h>
#include <assert.h>

#include "linkedlist.h"

int x1 = 1, x2 = 2, x3 = 3, x4 = 4;
node_t *node1 = NULL, *node2 = NULL, *node3 = NULL, *node4 = NULL;

/****************************** Recursive Flip List ***************************/

node_t *RecFlipList(node_t *node)
{
    node_t *new_head = NULL;
    
    if (NULL == node->next)
    {
        return node;
    }
    
    new_head = RecFlipList(node->next);
    node->next->next = node;
    node->next = NULL;
    
    return new_head;
}

node_t *FlipList(node_t *head)
{
    assert(NULL != head);
    return RecFlipList(head);    
}

/******************************** Initialize List *****************************/

static node_t *InitList()
{    
    node1 = LLCreateNode(NULL, &x1);
    node2 = LLCreateNode(NULL, &x2);
    node3 = LLCreateNode(NULL, &x3);
    node4 = LLCreateNode(NULL, &x4);
    LLInsertAfter(node2, node1);
    LLInsertAfter(node3, node2);
    LLInsertAfter(node4, node3);
    
    return node1;
}

/********************************* Print List **********************************/ 

int PrintNode(void *node, void *additional) 
{ 
    (void)additional;
    printf("%d ", *(int*)(((node_t *)node)->data));
    
    return 0;
}

static void PrintList(node_t *node)
{
    LLForEach(node, &PrintNode, NULL);
}

int main ()
{
    node_t *head = InitList();
    printf("before flip: ");
    PrintList(head);    
    head = FlipList(head); 
    printf("\nafter flip: ");
    PrintList(head);
    printf("\n");
    
	return 0;
}

