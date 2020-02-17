#include <stdio.h> /* printf */

#include "circularbuffer.h" 

#define UNUSED(x) (void)(x)

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

static void Test1()
{
    cbuffer_t *cbuffer = CBufferCreate(25);
    
    
    CBufferDestroy(cbuffer);
}

int main()
{
    Test1();

    return 0;
}
