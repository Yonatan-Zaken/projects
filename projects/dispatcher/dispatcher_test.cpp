/**********************
    Dispatcher
    Test File
    02/05/2020
    ILRD - RD8081               
    Greg Markovsky
**********************/

#include "logger_preprocessor.hpp"
#include "tests.hpp" // RUN_TEST
#include "dispatcher.hpp" // Observer

using namespace ilrd;
using namespace std;

static void TestBasic(int voc);
static void TestUnsub(int voc);
static void TestSub(int voc);

int main()
{
	/* --- IGNORE - don't run test --------------- */
	/* --- SILENT - run test without details ----- */
	/* --- DETAIL - run test with full details --- */

    SET_LOG_PATHS("logger.txt", "INFO");
    LOG_INFO("Dispatcher - Observer Test Started");

	RUN_TEST( DETAIL , "Test basic observers", TestBasic);
    RUN_TEST( DETAIL , "Test unsunb mid broadcast", TestUnsub);
    RUN_TEST( DETAIL , "Test subscribe mid broadcast", TestSub);

	TestBottomLine("Dispatcher - Observer");

	return 0;
}

static void UpdateInt(int *num);
static void UpdateUnsub(int *num);
static void UpdateSub(int *num);
static void UpdateIntDeath();

typedef ObserverBase<int *> observerBase_t;
typedef Observer<int *> observer_t;
typedef Dispatcher<observerBase_t, int *> dispatcher_t;

static int g_deathCount = 0;
static Observer<int *> *observer = nullptr;
static dispatcher_t *dispatcher = nullptr;

/* ============================== Test Functions ============================ */
/* ------------------------------------------------------------ TestBasic --- */

static void TestBasic(int voc)
{
    g_deathCount = 0;

    dispatcher = new dispatcher_t;
    observer_t observer_1(dispatcher, &UpdateInt, &UpdateIntDeath);
    observer_t observer_2(dispatcher, &UpdateInt, &UpdateIntDeath);

    int testInt = 0;
    dispatcher->Broadcast(&testInt);
    TestInt(voc, "Simple Broadcast #1", 2, testInt);
    dispatcher->Broadcast(&testInt);
    TestInt(voc, "Simple Broadcast #2", 4, testInt);
    delete dispatcher;
    dispatcher = nullptr;
    TestInt(voc, "Destroy Dispatcher", 2, g_deathCount);
}

/* ------------------------------------------------------------ TestUnsub --- */

static void TestUnsub(int voc)
{
    g_deathCount = 0;

    dispatcher = new dispatcher_t;
    observer_t observer_1(dispatcher, &UpdateInt, &UpdateIntDeath);
    observer_t observer_2(dispatcher, &UpdateUnsub, &UpdateIntDeath);
    observer = new observer_t(dispatcher, &UpdateInt, &UpdateIntDeath);

    int testInt = 0;
    dispatcher->Broadcast(&testInt);
    TestInt(voc, "Broadcast with Unsub #1", 4, testInt);
    dispatcher->Broadcast(&testInt);
    TestInt(voc, "Broadcast with Unsub #2", 8, testInt);
    delete dispatcher;
    dispatcher = nullptr;
    TestInt(voc, "Destroy Dispatcher", 2, g_deathCount);
}

/* -------------------------------------------------------------- TestSub --- */

static void TestSub(int voc)
{
    g_deathCount = 0;

    dispatcher = new dispatcher_t;
    observer_t observer_1(dispatcher, &UpdateInt, &UpdateIntDeath);
    observer_t *observer_2 = new observer_t(dispatcher, &UpdateSub, 
                                            &UpdateIntDeath);

    int testInt = 0;
    dispatcher->Broadcast(&testInt);
    TestInt(voc, "Broadcast with Sub #1", 8, testInt);

    delete observer_2;
    observer_2 = nullptr;
    dispatcher->Broadcast(&testInt);
    TestInt(voc, "Broadcast with Sub #2", 10, testInt);

    delete dispatcher;
    dispatcher = nullptr;
    TestInt(voc, "Destroy Dispatcher", 2, g_deathCount);

    delete observer;
    observer = nullptr;
}

/* ============================ Service Functions =========================== */
/* ------------------------------------------------------------ UpdateInt --- */

static void UpdateInt(int *num)
{
    ++(*num);
}

/* ---------------------------------------------------------- UpdateUnsub --- */

static void UpdateUnsub(int *num)
{
    (*num) += 3;
    delete observer;
    observer = nullptr;
}

/* ------------------------------------------------------------ UpdateSub --- */

static void UpdateSub(int *num)
{
    (*num) += 7;
    observer = new observer_t(dispatcher, &UpdateInt, &UpdateIntDeath);
}

/* ------------------------------------------------------- UpdateIntDeath --- */

static void UpdateIntDeath()
{
    ++g_deathCount;
}

