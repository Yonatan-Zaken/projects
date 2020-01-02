/*********************************/
/*    Data Structures            */
/*    Single Linked List         */       
/*    Author :Guy Cohen Zedek    */
/*    Reviewed By:               */
/*    Date:    2/12/2019         */
/*                               */
/*********************************/

#include <stdio.h> /* printf */

#include "linkedlist.h"

#define UNUSED(x) (void)(x)
#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define RUN_TEST(test)\
{\
  if(test)\
  {\
    printf(GREEN);\
    printf("SUCCESS\n");\
    printf(RESET);\
  }\
  else\
  {\
    printf(RED);\
    printf("FAIL \n");\
    printf(RESET);\
  }\
}

int PrintNode(void *node, void *additional) 
{
    node_t *n = (node_t*)node;
    
    UNUSED(additional);
    
    printf("data: %d\n", *(int*)n->data);
    
    return 0;
}

int IsMatch(void *node, void *additional)
{
    node_t *n = (node_t*)node;
    
    return (*(int*)n->data == *(int*)additional);
}

static void TestLinkedList()
{
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5;
    node_t *head = NULL, *node1 = NULL, *node2 = NULL, *node3 = NULL, *node4 =NULL;
    
    printf("Linked List 1:\n");
    node1 = LLCreateNode(NULL, &x1);
    node2 = LLCreateNode(NULL, &x2);
    node3 = LLCreateNode(NULL, &x3);
    node4 = LLCreateNode(NULL, &x4);
    head = node1;
    
    RUN_TEST(0 == LLInsertAfter(node2, node1));
    RUN_TEST(0 == LLInsertAfter(node3, node2));
    RUN_TEST(0 == LLInsertAfter(node4, node3));
    
    RUN_TEST(4 == LLSize(node1));
    head = LLFlip(head);
    RUN_TEST(node4 == head);
    LLDestroy(node4);
    
    printf("\nLinked List 2:\n");
    node1 = LLCreateNode(NULL, &x1);
    node2 = LLCreateNode(NULL, &x2);
    node3 = LLCreateNode(NULL, &x3);
    node4 = LLCreateNode(NULL, &x4);
    
    RUN_TEST(0 == LLInsertAfter(node2, node1));
    RUN_TEST(0 == LLInsertAfter(node3, node2));
    RUN_TEST(0 == LLInsertAfter(node4, node3));
    
    RUN_TEST(4 == LLSize(node1));
    LLFlip(node2);
    RUN_TEST(3 == LLSize(node4));
    RUN_TEST(2 == LLSize(node1));
    RUN_TEST(node3 == node4->next);
    RUN_TEST(node2 == LLFindIntersection(node1, node4));
    LLFlip(node4);
    LLDestroy(node1);
    
    printf("\nLinked List 3:\n");
    node1 = LLCreateNode(NULL, &x1);
    node2 = LLCreateNode(NULL, &x2);
    node3 = LLCreateNode(NULL, &x3);
    node4 = LLCreateNode(NULL, &x4);
    
    head = node1;
    
    RUN_TEST(0 == LLInsert(node2, node1));
    RUN_TEST(0 == LLInsert(node3, node1));
    RUN_TEST(0 == LLInsert(node4, node1));
    
    RUN_TEST(4 == *(int*)node1->data);  
    RUN_TEST(1 == *(int*)node2->data);
    RUN_TEST(2 == *(int*)node3->data);
    RUN_TEST(3 == *(int*)node4->data);
    RUN_TEST(4 == LLSize(node1));
    
    RUN_TEST(0 == LLForEach(head, &PrintNode, 0));
    LLRemove(node3);
    RUN_TEST(3 == LLSize(node1));
    LLRemoveAfter(node1);
    RUN_TEST(2 == LLSize(node1));
    LLRemove(node1);
    RUN_TEST(1 == LLSize(node1));
    LLDestroy(node1);
    
    printf("\nLinked List 4:\n");
    node1 = LLCreateNode(NULL, &x1);
    node2 = LLCreateNode(NULL, &x2);
    node3 = LLCreateNode(NULL, &x3);
    node4 = LLCreateNode(NULL, &x4);
    head = node1;
    
    RUN_TEST(0 == LLInsertAfter(node2, node1));
    RUN_TEST(0 == LLInsertAfter(node3, node2));
    RUN_TEST(0 == LLInsertAfter(node4, node3));
    
    RUN_TEST(node3 == LLGetNode(head, &IsMatch, &x3));
    RUN_TEST(NULL == LLGetNode(head, &IsMatch, &x5));
    RUN_TEST(4 == LLSize(node1));
    
    LLDestroy(node1);
    
    printf("\nLinked List 5:\n");
    node4 = LLCreateNode(NULL, &x4);
    node3 = LLCreateNode(node4, &x3);
    node2 = LLCreateNode(node3, &x2);
    node1 = LLCreateNode(node2, &x1);
    
    node4->next = node1;
    
    RUN_TEST(1 == LLHasLoop(node1));
    
    node4->next = NULL;
    LLDestroy(node1);
}

int main()
{
    TestLinkedList();
    return 0;
}
