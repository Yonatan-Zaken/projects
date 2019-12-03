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
    node1 = SLLCreateNode(NULL, &x1);
    node2 = SLLCreateNode(NULL, &x2);
    node3 = SLLCreateNode(NULL, &x3);
    node4 = SLLCreateNode(NULL, &x4);
    head = node1;
    
    RUN_TEST(0 == SLLInsertAfter(node2, node1));
    RUN_TEST(0 == SLLInsertAfter(node3, node2));
    RUN_TEST(0 == SLLInsertAfter(node4, node3));
    
    RUN_TEST(4 == SLLSize(node1));
    head = SLLFlip(head);
    RUN_TEST(node4 == head);
    SLLDestroy(node4);
    
    printf("\nLinked List 2:\n");
    node1 = SLLCreateNode(NULL, &x1);
    node2 = SLLCreateNode(NULL, &x2);
    node3 = SLLCreateNode(NULL, &x3);
    node4 = SLLCreateNode(NULL, &x4);
    
    RUN_TEST(0 == SLLInsertAfter(node2, node1));
    RUN_TEST(0 == SLLInsertAfter(node3, node2));
    RUN_TEST(0 == SLLInsertAfter(node4, node3));
    
    RUN_TEST(4 == SLLSize(node1));
    SLLFlip(node2);
    RUN_TEST(3 == SLLSize(node4));
    RUN_TEST(2 == SLLSize(node1));
    RUN_TEST(node3 == node4->next);
    RUN_TEST(node2 == SLLFindIntersection(node1, node4));
    SLLFlip(node4);
    SLLDestroy(node1);
    
    printf("\nLinked List 3:\n");
    node1 = SLLCreateNode(NULL, &x1);
    node2 = SLLCreateNode(NULL, &x2);
    node3 = SLLCreateNode(NULL, &x3);
    node4 = SLLCreateNode(NULL, &x4);
    
    head = node1;
    
    RUN_TEST(0 == SLLInsert(node2, node1));
    RUN_TEST(0 == SLLInsert(node3, node1));
    RUN_TEST(0 == SLLInsert(node4, node1));
    
    RUN_TEST(4 == *(int*)node1->data);  
    RUN_TEST(1 == *(int*)node2->data);
    RUN_TEST(2 == *(int*)node3->data);
    RUN_TEST(3 == *(int*)node4->data);
    RUN_TEST(4 == SLLSize(node1));
    
    RUN_TEST(0 == SLLForEach(head, &PrintNode, 0));
    SLLRemove(node3);
    RUN_TEST(3 == SLLSize(node1));
    SLLRemoveAfter(node1);
    RUN_TEST(2 == SLLSize(node1));
    SLLRemove(node1);
    RUN_TEST(1 == SLLSize(node1));
    SLLDestroy(node1);
    
    printf("\nLinked List 4:\n");
    node1 = SLLCreateNode(NULL, &x1);
    node2 = SLLCreateNode(NULL, &x2);
    node3 = SLLCreateNode(NULL, &x3);
    node4 = SLLCreateNode(NULL, &x4);
    head = node1;
    
    RUN_TEST(0 == SLLInsertAfter(node2, node1));
    RUN_TEST(0 == SLLInsertAfter(node3, node2));
    RUN_TEST(0 == SLLInsertAfter(node4, node3));
    
    RUN_TEST(node3 == SLLGetNode(head, &IsMatch, &x3));
    RUN_TEST(NULL == SLLGetNode(head, &IsMatch, &x5));
    RUN_TEST(4 == SLLSize(node1));
    
    SLLDestroy(node1);
    
    printf("\nLinked List 5:\n");
    node4 = SLLCreateNode(NULL, &x4);
    node3 = SLLCreateNode(node4, &x3);
    node2 = SLLCreateNode(node3, &x2);
    node1 = SLLCreateNode(node2, &x1);
    
    node4->next = node1;
    
    RUN_TEST(1 == SLLHasLoop(node1));
    
    node4->next = NULL;
    SLLDestroy(node1);
}

int main()
{
    TestLinkedList();
    return 0;
}
