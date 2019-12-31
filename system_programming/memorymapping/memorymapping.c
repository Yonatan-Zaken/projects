#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONST 5

char *stringliteral3;      
char *stringliteral2 = "555";  
int globalnoninit;
char global = 'A';
static int global1;
static int global2 = 0;
static int globalinit = 4;
const int globalnoinit;
const int global3 = 0;
const static int global4;
const static int global5 = 0;
const static int global6 = 2;

static void StaticFunc(float x, int y)
{
    int a = 3;
    int b;
    const c = 0;    
}

extern void ExternFunc()
{
    int local1 = 3;
    static float local2;
    static float local3 = 5.0;
    const static int local4 = 5;
    printf("local 1 %d\n", local1);
    printf("local 3 %f\n", local3);
    
}

int main(int argc, char *argv[], char *envp[])
{
    char *heap1 = (char *)malloc(20);    
    void *heap2 = (void *)malloc(50);
    char *stringliteral = "memorymapping";  
    float x = 20.0;
    int y = 30;
    
    strcpy(heap1, stringliteral);
    printf("argc %d\n", argc);
    printf("heap1 %s\n", heap1);
    printf("envp %s\n", envp[10]);
    printf("argv %s\n", argv[0]);
    printf("argv %s\n", argv[1]);
    printf("argv %s\n", argv[2]);
    
    StaticFunc(x, y);
    ExternFunc();
    free(heap1); heap1 = NULL;
    free(heap2); heap2 = NULL;
    
    return 0;
}
