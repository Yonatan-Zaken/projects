/*********************************/
/*   			             	 */
/*   Main file DS 3              */
/*   Yonatan Zaken		         */
/*   Last Updated 1/12/19        */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/


#include <stdio.h>   /* printf */
#include <string.h>  /* strcpy, strcmp */
#include <stdlib.h>  /* malloc */

#include "vector.h"   /* stack data structure functions */

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

struct Vector
{
    void *start;
    size_t size;
    size_t capacity;
    size_t element_size;    
};

static void TestVector1()
{
    size_t element_size = 4;
    size_t capacity = 5;
    int i = 0;
    vector_t* vector1 = VectorCreate(element_size, capacity);
    
    printf("vector1 test:\n");
    
    RUN_TEST(0 == vector1->size, "check vector1 size");
    RUN_TEST(5 == vector1->capacity, "check vector1 capacity");
    RUN_TEST(4 == vector1->element_size, "check vector1 elementsize");
    
    for (; i < 10; ++i)
    {
        RUN_TEST(0 == VectorPushBack(vector1, &i), "check vector1 push");
    }
    
    printf("capacity: %lu, size: %lu\n", vector1->capacity, vector1->size);
    RUN_TEST(0 == VectorPushBack(vector1, &i), "check vector1 push");
    printf("capacity: %lu, size: %lu\n", vector1->capacity, vector1->size);
    
    for(i = 0; i < 6; ++i)
    {
        VectorPopBack(vector1);    
    }
        
    printf("capacity: %lu, size: %lu\n", vector1->capacity, vector1->size);
    
    for(i = 0; i < 6; ++i)
    {
        VectorPopBack(vector1);    
    }
    
    printf("capacity: %lu, size: %lu\n", vector1->capacity, vector1->size);
    
    printf("\n");
    VectorDestroy(vector1);    
}

static void TestVector2()
{
    size_t element_size = 4;
    size_t capacity = 3;
    float i = 0.0;
    vector_t* vector2 = VectorCreate(element_size, capacity);
    
    printf("vector2 test:\n");
    
    VectorPopBack(vector2);
    VectorPopBack(vector2);
    VectorPopBack(vector2);
    printf("capacity: %lu, size: %lu\n", vector2->capacity, vector2->size);
    
    for (i = 2.5; i <= 10.0; ++i)
    {
        RUN_TEST(0 == VectorPushBack(vector2, &i), "check vector1 push");        
    }
    
    RUN_TEST(12 == VectorCapacity(vector2), "check vector2 capactiy");
    RUN_TEST(8 == VectorSize(vector2), "check vector2 size");
    
    printf("capacity: %lu, size: %lu\n", vector2->capacity, vector2->size);
    RUN_TEST(9.5 == *(float*)VectorGetItemAddress(vector2, 8), 
                                      "vector2 item address");
    
    for (i = 0; i < 7; ++i)
    {
        VectorPopBack(vector2);
    }
    
    printf("capacity: %lu, size: %lu\n", vector2->capacity, vector2->size);
    RUN_TEST(2.5 == *(float*)VectorGetItemAddress(vector2, 1), 
                                      "vector2 item address");
    
    RUN_TEST(1 == VectorSize(vector2), "check vector2 size");
    VectorPopBack(vector2);
    RUN_TEST(0 == VectorSize(vector2), "check vector2 size");
    
    RUN_TEST(NULL == VectorGetItemAddress(vector2, 3), "vector2 item address");
    RUN_TEST(NULL == VectorGetItemAddress(vector2, 0), "vector2 item address");
    
    printf("\n");
    VectorDestroy(vector2);   
}

static void TestVector3()
{
    size_t element_size = 1;
    size_t capacity = 10;
    int i = 0;
    vector_t* vector3 = VectorCreate(element_size, capacity);
    
    printf("vector3 test:\n");
    
    RUN_TEST(0 == vector3->size, "check vector1 size");
    RUN_TEST(10 == vector3->capacity, "check vector1 capacity");
    RUN_TEST(1 == vector3->element_size, "check vector1 elementsize");
    VectorPopBack(vector3);
    VectorPopBack(vector3);
    VectorPopBack(vector3);
    printf("capacity: %lu, size: %lu\n", vector3->capacity, vector3->size);
    
    for (i = 65; i < 76; ++i)
    {
        RUN_TEST(0 == VectorPushBack(vector3, &i), "check vector3 push");
        printf("capacity: %lu, size: %lu\n", vector3->capacity, vector3->size);
    }    
    
    RUN_TEST('J' == *(char*)VectorGetItemAddress(vector3, 10), "check vector3 IA");
    
    for (i = 65; i < 76; ++i)
    {
        VectorPopBack(vector3);
        printf("capacity: %lu, size: %lu\n", vector3->capacity, vector3->size);
    }
    
    
    
    
    printf("\n");
    VectorDestroy(vector3); 
}

int main()
{   
    TestVector1();
    TestVector2();
    TestVector3();
    
    return 0;
}
