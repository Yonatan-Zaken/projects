/*********************************/
/*   			             	 */
/*   Main file DS 4              */
/*   Yonatan Zaken		         */
/*   Last Updated 2/12/19        */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "linkedlist.h" /* linked list functions */

#define NORMAL "\033[0m"
#define RED "\033[;031m"
#define GREEN "\033[;032m"

#define RUN_TEST(test, error_message){\
    if (test)\
    {\
        printf(GREEN);\
        printf("SUCCESS\n");\
        printf(NORMAL);\
    }\
    else\
    {\
        printf(RED);\
        printf("FAIL %s\n", error_message);\
        printf(NORMAL);\
    }\
}

static void TestLinkedList1()
{
    int data1 = 77;
    float data2 = 2.5;
    char data3 = 'Q';
    int data4 = 99;
    node_t *node1 = NULL;
    node_t *node2 = NULL;
    node_t *node3 = NULL;
    node_t *node4 = NULL;
    
    printf("Test Linked List 1:\n");
    node1 = LLCreateNode(NULL, &data1);
    node2 = LLCreateNode(NULL, &data2);
    node3 = LLCreateNode(NULL, &data3);
    
    RUN_TEST(77 == *(int*)node1->data, "Check data test 1");
    RUN_TEST(0 == LLInsertAfter(node1, node2), "Check Insert test1");
    RUN_TEST(0 == LLInsertAfter(node2, node3), "Check Insert test1");
    RUN_TEST(3 == LLSize(node1), "Size of list before remove test1");
    
    printf("%d\n", *(int*)node1->data);
    printf("%f\n", *(float*)node2->data);
    printf("%c\n", *(char*)node3->data);
    
    LLRemove(node2);
    RUN_TEST(2 == LLSize(node1), "Size of list after remove test1");
    
    node4 = LLCreateNode(NULL, &data4);
    RUN_TEST(0 == LLInsert(node4, node2), "Check Insert test1");
    RUN_TEST(3 == LLSize(node1), "Size of list after remove test1");
    printf("%d\n", *(int*)node1->data);
    printf("%d\n", *(int*)node2->data);
    printf("%c\n", *(char*)node4->data);
    
    LLRemoveAfter(node1);
    RUN_TEST(2 == LLSize(node1), "Size of list after remove test1");
    
    LLDestroy(node1);
    printf("\n");
}

int main()
{
    TestLinkedList1();
    
    return 0;
}
