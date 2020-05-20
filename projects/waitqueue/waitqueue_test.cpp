/**********************
    Waitable Queue
    Test File
    18/05/2020
    ILRD - RD8081             
    Greg Markovsky
**********************/

#include <queue> // std::queue
#include <pthread.h> // threads
#include <unistd.h> // sleep

#include "tests.hpp" // RUN_TEST
#include "waitqueue.hpp" // WaitableQueue

using namespace ilrd;
using namespace std;

static void TestBasic(int voc);
static void TestWait(int voc);
static void TestTimedWait(int voc);
static void TestTimedWaitTimeOut(int voc);

static void *DoPop(void *threadArg);
static void *DoTimedPop(void *threadArg);
static void *DoPush(void *threadArg);

typedef WaitableQueue< std::queue<int> > intWQueue_t;
typedef std::pair<intWQueue_t *, int> threadArg_t;
typedef boost::chrono::nanoseconds nanoSec_t;
typedef boost::chrono::seconds seconds_t;

static int chrono_sync = 0;
static int wait_time = 0;

int main()
{
	/* --- IGNORE - don't run test --------------- */
	/* --- SILENT - run test without details ----- */
	/* --- DETAIL - run test with full details --- */

	RUN_TEST( DETAIL , "Test Basic Operations", TestBasic);
    RUN_TEST( DETAIL , "Test Waitable Queue Operations", TestWait);
    RUN_TEST( DETAIL , "Test timeoutPop - No Timeout", TestTimedWait);
    RUN_TEST( DETAIL , "Test timeoutPop - Timeout", TestTimedWaitTimeOut);

	TestBottomLine("Waitable Queue");

	return 0;
}

/* ============================== Test Functions ============================ */
/* ------------------------------------------------------------ TestBasic --- */

static void TestBasic(int voc)
{
    intWQueue_t wQueue;

    TestInt(voc, "IsEmpty - many elements", true, wQueue.IsEmpty());
    wQueue.Push(10);
    TestInt(voc, "IsEmpty - single element", false, wQueue.IsEmpty());
    int x;
    wQueue.Pop(x);
    TestInt(voc, "Push/Pop single", 10, x);

    wQueue.Push(7);  
    wQueue.Push(8);
    wQueue.Push(9);
    TestInt(voc, "IsEmpty - multipile elements", false, wQueue.IsEmpty());
    wQueue.Pop(x);
    TestInt(voc, "Push/Pop FIFO ORDER", 7, x);
    wQueue.Pop(x);
    TestInt(voc, "Push/Pop FIFO ORDER", 8, x);
    wQueue.Pop(x);
    TestInt(voc, "Push/Pop FIFO ORDER", 9, x);
}

/* ------------------------------------------------------------- TestWait --- */

static void TestWait(int voc)
{
    intWQueue_t wQueue;
    threadArg_t threadArg(&wQueue, voc);
    chrono_sync = 0;

    pthread_t popThread;
    pthread_create(&popThread, nullptr, DoPop, &threadArg);

    sleep(2);

    pthread_t pushThread;
    pthread_create(&pushThread, nullptr, DoPush, &threadArg);

    pthread_join(popThread, nullptr);
    pthread_join(pushThread, nullptr);

    TestInt(voc, "Wait Push/Pop excange", true, wQueue.IsEmpty());  
}

/* -------------------------------------------------------- TestTimedWait --- */

static void TestTimedWait(int voc)
{
    intWQueue_t wQueue;
    threadArg_t threadArg(&wQueue, voc);
    chrono_sync = 0;

    pthread_t popThread;
    pthread_create(&popThread, nullptr, DoTimedPop, &threadArg);

    wait_time = 1;
    sleep(wait_time);

    pthread_t pushThread;
    pthread_create(&pushThread, nullptr, DoPush, &threadArg);

    pthread_join(popThread, nullptr);
    pthread_join(pushThread, nullptr);

    TestInt(voc, "Wait Push/Pop excange", true, wQueue.IsEmpty());  
}

/* ------------------------------------------------- TestTimedWaitTimeOut --- */

static void TestTimedWaitTimeOut(int voc)
{
    intWQueue_t wQueue;
    threadArg_t threadArg(&wQueue, voc);
    chrono_sync = 0;

    wait_time = 4;
    pthread_t popThread;
    pthread_create(&popThread, nullptr, DoTimedPop, &threadArg);

    sleep(wait_time);

    pthread_t pushThread;
    pthread_create(&pushThread, nullptr, DoPush, &threadArg);

    pthread_join(popThread, nullptr);
    pthread_join(pushThread, nullptr);

    TestInt(voc, "Wait Push/Pop excange", false, wQueue.IsEmpty());  
}

/* ============================ Service Functions =========================== */
/* ---------------------------------------------------------------- DoPop --- */

static void *DoPop(void *threadArg)
{
    intWQueue_t *wQueue = reinterpret_cast<threadArg_t *>(threadArg)->first;
    int voc = reinterpret_cast<threadArg_t *>(threadArg)->second;

    ++chrono_sync;
    TestInt(voc, "Wait Order 1", 1, chrono_sync);

    int x;
    try
    {
        wQueue->Pop(x);
        ++chrono_sync;
        TestInt(voc, "Wait Order 3", 3, chrono_sync);
    }
    catch (...)
    {
        TestInt(voc, "Waiting Pop - Unwanted Exception Thrown", 0, 1);
    }
    
    TestInt(voc, "Waiting Pop - Value", 7, x);

    return nullptr;
}

/* ----------------------------------------------------------- DoTimedPop --- */

static void *DoTimedPop(void *threadArg)
{
    intWQueue_t *wQueue = reinterpret_cast<threadArg_t *>(threadArg)->first;
    int voc = reinterpret_cast<threadArg_t *>(threadArg)->second;

    ++chrono_sync;
    TestInt(voc, "Wait Order 1", 1, chrono_sync);

    int x;
    try
    {
        seconds_t seconds(2);
        nanoSec_t nanoSec = seconds;
        //nanoSec_t nanoSec(3000000000);
        bool status = wQueue->Pop(x, nanoSec);

        if (3 < wait_time)
        {
            ++chrono_sync;
            TestInt(voc, "Wait Order 2", 2, chrono_sync);            
            TestInt(voc, "TimedPop Timout - On", false, status);
        }
        else
        {
            ++chrono_sync;
            TestInt(voc, "Wait Order 3", 3, chrono_sync);
            TestInt(voc, "TimedPop Timout - Off", true, status);
            TestInt(voc, "Waiting Pop - Value", 7, x);
        } 
    }
    catch (...)
    {
        TestInt(voc, "Waiting Pop - Unwanted Exception Thrown", 0, 1);
    }
    
    return nullptr;
}

/* --------------------------------------------------------------- DoPush --- */

static void *DoPush(void *threadArg)
{
    intWQueue_t *wQueue = reinterpret_cast<threadArg_t *>(threadArg)->first;
    int voc = reinterpret_cast<threadArg_t *>(threadArg)->second;

    if (3 < wait_time)
    {
        ++chrono_sync;
        TestInt(voc, "Wait Order 3", 3, chrono_sync);            
    }
    else
    {
        ++chrono_sync;
        TestInt(voc, "Wait Order 2", 2, chrono_sync);
    } 

    wQueue->Push(7);

    return nullptr; 
}