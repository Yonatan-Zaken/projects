/*********************************/
/*   			             	 */
/*   System Programming          */
/*   UID                         */
/*   Author: Yonatan Zaken       */
/*   Last Updated 15/12/19       */
/*   Reviewed by: Guy            */   
/*			                   	 */
/*********************************/

#include <stdio.h> /* printf */

#include "uid.h"

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

#define MAX_UID 10
/*
struct Uid
{
    time_t time_stamp;
    size_t counter;
    pid_t pid;
};
*/
static ilrd_uid_t g_arr[MAX_UID];

static void PrintUID()
{
    int  i = 0;
    
    for (; i < MAX_UID; ++i)
    {
        printf("UID: %d\nCounter: %lu\nTime Stamp: %ld\n\n", g_arr[i].pid,
                                                             g_arr[i].counter,
                                                             g_arr[i].time_stamp);
    } 
}

static void UidTest1()
{
    int  i = 0;
   
    g_arr[i] = UIDCreate();
    
   
    for (i = 1; i < MAX_UID; ++i)
    {
        g_arr[i] = UIDCreate();
    } 
    
    g_arr[1].counter = 0;
    g_arr[1].time_stamp = g_arr[0].time_stamp;
                                                                                                                                      
}

static void TestIsBad()
{
    int flag = 0, i = 0;
    for (; i < MAX_UID && !flag; ++i)
    {
        flag = UIDIsBad(g_arr[i]);
    }
    
    if (1 == flag)
    {
        printf("Bad UID!\n");
    } 
}

static void TestIsSame()
{
    int i = 0, j = 0, flag = 0;
    
    for (; i < MAX_UID && !flag; ++i)
    {
        for (j = i + 1; j < MAX_UID && !flag; ++j)
        {
            flag = UIDIsSame(g_arr[i], g_arr[j]);
        }
    }
    
    if (1 == flag)
    {
        printf("Same UID:\n");
        printf("UID %d: %d\nCounter: %lu\nTime Stamp: %ld\n\n", i, g_arr[i].pid,
                                                                   g_arr[i].counter,
                                                                   g_arr[i].time_stamp);
        printf("UID %d: %d\nCounter: %lu\nTime Stamp: %ld\n\n", j, g_arr[i].pid,
                                                                   g_arr[i].counter,
                                                                   g_arr[i].time_stamp);
    } 
}

int main()
{
    UidTest1();
    
    PrintUID();
    
    TestIsBad();
    
    TestIsSame();
    
    return 0;
}
