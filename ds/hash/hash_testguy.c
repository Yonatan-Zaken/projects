#include <math.h> /* pow */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */
#include "utilities.h" /* RUN_TEST */

#include "hash.h"

#define MAX_SIZE 30
#define TABLE_SIZE 1000

static size_t HashFunctionForInt(const void *data)
{   
    assert(NULL != data);
     
    return (((int)pow(*(int *)data, 3)) % 100);
}

static size_t HashFunctionForString(const void *data)
{    
    char *runner = (void *)data;
    size_t sum = 0;

    
    assert(NULL != data);
    
    while ('\0' != *runner)
    {
        sum += ((*runner) % 50);
        ++runner;
    }
    
    return sum;
}

static int IsMatchInt(void *data1, void *data2)
{
    return (*(int *)data1 == *(int *)data2); 
}

static int IsMatchString(void *data1, void *data2)
{
    return (0 == strcmp((char*)data1, (char*)data2)); 
}

static int PrintInt(void *data, void *param)
{
    UNUSED(param);
    
    printf("%d\n", *(int *)data);
    
    return 0;
}

static int PrintString(void *data, void *param)
{
    UNUSED(param);
    
    printf("%s\n", (char *)data);
    
    return 0;
}

static void TestCreate()
{
    hash_t *table = HashCreate(TABLE_SIZE, HashFunctionForInt, IsMatchInt);

    printf("Create:\n");
    RUN_TEST(0 == HashSize(table));
    RUN_TEST(1 == HashIsEmpty(table));

    HashDestroy(table);
}

static void TestInsertInt()
{
    hash_t *table = HashCreate(TABLE_SIZE, HashFunctionForInt, IsMatchInt);
    int x1 = 8, x2 = 23;
    
    printf("\nInsert Int:\n");
    RUN_TEST(0 == HashSize(table));
    RUN_TEST(1 == HashIsEmpty(table));
    
    RUN_TEST(0 == HashInsert(table, &x1));
    RUN_TEST(0 == HashInsert(table, &x2));
    RUN_TEST(2 == HashSize(table));    
    RUN_TEST(0 == HashForeach(table, PrintInt, NULL));
    
    HashDestroy(table);
}

static void TestInsertString()
{
    hash_t *table = HashCreate(1, HashFunctionForString, IsMatchString);
    char str1[] = "Hello World", str2[] = "hello world", str3[] = "abc";
    
    printf("\nInsert String:\n");
    RUN_TEST(0 == HashSize(table));
    RUN_TEST(1 == HashIsEmpty(table));
    
    RUN_TEST(0 == HashInsert(table, str1));
    RUN_TEST(0 == HashInsert(table, str2));
    RUN_TEST(0 == HashInsert(table, str3));
    RUN_TEST(3 == HashSize(table));
    RUN_TEST(0 == HashForeach(table, PrintString, NULL));
    
    HashRemove(table, str1);
    
    RUN_TEST(2 == HashSize(table));
    RUN_TEST(0 == HashForeach(table, PrintString, NULL));
    
    RUN_TEST(0 == strcmp(str2, HashFind(table, str2)));
    RUN_TEST(0 == HashForeach(table, PrintString, NULL));
    
    HashDestroy(table);
}

static void TestDictionary()
{
    hash_t *table = HashCreate(10, HashFunctionForString, IsMatchString);
    char buffer[TABLE_SIZE][MAX_SIZE];
    char *path = "/usr/share/dict/words";
    FILE *fp;
    size_t i = 0;
      
    printf("\nInsert Dictionary:\n");
    RUN_TEST(0 == HashSize(table));
    RUN_TEST(1 == HashIsEmpty(table));
    
    fp = fopen(path, "r");
    
    for(i = 0; i < TABLE_SIZE; ++i)
    {
        if (NULL == fgets(*(buffer + i), MAX_SIZE, fp))
        {
            break;
        }
        HashInsert(table, *(buffer + i));
    }
    
    fclose(fp);
    
    RUN_TEST(TABLE_SIZE == HashSize(table));
    
    for(i = 0; i < TABLE_SIZE ; i += 2)
    {
        HashRemove(table, *(buffer+i));
    }
    
    RUN_TEST(500 == HashSize(table));
    
    for (i = 1; i < TABLE_SIZE; i += 2)
    {
        HashRemove(table, *(buffer+i));
    }
    
    RUN_TEST(0 == HashSize(table));
 
    RUN_TEST(0 == HashForeach(table, PrintString, NULL));
       
    HashDestroy(table);
}

int main()
{
    TestCreate();
    TestInsertInt();
    TestInsertString();
    TestDictionary();
    
	return 0;
}
