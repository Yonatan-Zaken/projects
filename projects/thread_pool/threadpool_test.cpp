/**********************
    Thread Pool
    Test File
    26/05/2020
    ILRD - RD8081               
    Greg Markovsky
**********************/

#include "tests.hpp" // RUN_TEST
#include "thread_pool.hpp" // ThreadPool

using namespace ilrd;
using namespace std;

/* =========================== Test Classes ================================= */

boost::mutex g_counterLock;
static int g_counter = 0;
static int g_priority_1 = 0;
static int g_priority_2 = 0;
static int g_priority_3 = 0;
static const boost::chrono::seconds g_timeout(1);

class TaskCount : public ThreadPool::Task
{
public:
    virtual void Run() 
    {
        boost::mutex::scoped_lock lock(g_counterLock); 
        ++g_counter; 
    }
};

class TaskPrior1 : public ThreadPool::Task
{
public:
    virtual void Run() 
    { 
        boost::mutex::scoped_lock lock(g_counterLock);
        g_priority_1 = g_priority_3; 
    }
};

class TaskPrior2 : public ThreadPool::Task
{
public:
    virtual void Run()
    { 
        boost::mutex::scoped_lock lock(g_counterLock);
        g_priority_2 = g_priority_1 + 5;
    }
};

class TaskPrior3 : public ThreadPool::Task
{
public:
    virtual void Run()
    { 
        boost::mutex::scoped_lock lock(g_counterLock);
        g_priority_3 += g_priority_1 + g_priority_2;
    }
};

static void TestSingleTask(int voc);
static void TestMultiTask(int voc);
static void TestPriority(int voc);
static void TestPause(int voc);
static void TestNumOfThreads(int voc);

int main()
{
	/* --- IGNORE - don't run test --------------- */
	/* --- SILENT - run test without details ----- */
	/* --- DETAIL - run test with full details --- */

    char envFilePath[] = "ILRD_LOGGER_FILE_PATH=/home/student/git/projects/logger/logger.txt";
    char envLogLevel[] = "ILRD_LOGGER_LEVEL=DEBUG";
    putenv(envFilePath);
    putenv(envLogLevel);

	RUN_TEST( DETAIL , "Test Single Task", TestSingleTask);
	RUN_TEST( DETAIL , "Test Multi Task", TestMultiTask);
    RUN_TEST( DETAIL , "Test Priority", TestPriority);
    RUN_TEST( DETAIL , "Test Pause", TestPause);
    RUN_TEST( DETAIL , "Test Get/Set Num of Threads", TestNumOfThreads);

	TestBottomLine("Thread Pool");

	return 0;
}

/* ============================== Test Functions ============================ */
/* ------------------------------------------------------- TestSingleTask --- */

static void TestSingleTask(int voc)
{
    g_counter = 0;

    ThreadPool::task_t taskCount(new TaskCount);
    ThreadPool threadPool(4, g_timeout);

    threadPool.Add(taskCount, ThreadPool::MEDIUM);
    sleep(1);
    TestInt(voc, "Add/Run - Wait for start", 0, g_counter);

    threadPool.Start();
    sleep(1);
    TestInt(voc, "Add/Run - Single task", 1, g_counter);
}

/* -------------------------------------------------------- TestMultiTask --- */

static void TestMultiTask(int voc)
{
    g_counter = 0;

    ThreadPool::task_t taskCount(new TaskCount);
    ThreadPool threadPool(8, g_timeout);

    for (int i = 0; i < 1000; ++i)
    {
        threadPool.Add(taskCount, ThreadPool::MEDIUM);
    }

    threadPool.Start();
    sleep(3);
    TestInt(voc, "Add/Run - 1000 tasks", 1000, g_counter);

    threadPool.Stop(g_timeout);
}

/* --------------------------------------------------------- TestPriority --- */

static void TestPriority(int voc)
{
    g_counter = 0;

    ThreadPool::task_t taskCount(new TaskCount);
    ThreadPool::task_t taskPrior1(new TaskPrior1);
    ThreadPool::task_t taskPrior3(new TaskPrior3);
    ThreadPool::task_t taskPrior2(new TaskPrior2);
    ThreadPool threadPool(1, g_timeout); // 1 is important for the test!

    g_priority_1 = 0;
    g_priority_2 = 0;
    g_priority_3 = 1;

    threadPool.Add(taskCount, ThreadPool::HIGH);
    threadPool.Add(taskPrior2, ThreadPool::MEDIUM);
    threadPool.Add(taskPrior3, ThreadPool::LOW);
    threadPool.Add(taskPrior1, ThreadPool::HIGH);
    threadPool.Add(taskPrior3, ThreadPool::HIGH);

    threadPool.Start();
    sleep(2);
    TestInt(voc, "Priority - Correct order", 1, g_priority_1);
    TestInt(voc, "Priority - Correct order", 6, g_priority_2);
    TestInt(voc, "Priority - Correct order", 9, g_priority_3);

    //threadPool.Stop(boost::chrono::nanoseconds(1));
}

/* ------------------------------------------------------------ TestPause --- */

static void TestPause(int voc)
{
    g_counter = 0;
    ThreadPool::task_t taskCount(new TaskCount);
    ThreadPool threadPool(4, g_timeout);

    for (int i = 0; i < 400000; ++i)
    {
        threadPool.Add(taskCount, ThreadPool::MEDIUM);
    }
    threadPool.Start();
    sleep(1);
    threadPool.Pause();
    int checkCounter = g_counter;
    sleep(1);
    TestIntApp(voc, "Pause", checkCounter, g_counter, 4);
    threadPool.Start();
    sleep(5);
    TestInt(voc, "Start after Pause", 400000, g_counter);
}

/* ----------------------------------------------------- TestNumOfThreads --- */

static void TestNumOfThreads(int voc)
{
    g_counter = 0;
    ThreadPool emptyPool(0, g_timeout);
    TestInt(voc, "GetNumOfThreads - none", 0, emptyPool.GetNumOfThreads());

    ThreadPool::task_t taskCount(new TaskCount);
    ThreadPool threadPool(4, g_timeout);
    TestInt(voc, "GetNumOfThreads - some", 4, threadPool.GetNumOfThreads());

    for (int i = 0; i < 800000; ++i)
    {
        threadPool.Add(taskCount, ThreadPool::MEDIUM);
    }
    threadPool.Start();
    sleep(1);
    threadPool.SetNumOfThreads(10);
    sleep(1);
    TestInt(voc, "SetNumOfThreads - increase", 10, threadPool.GetNumOfThreads());
    sleep(1);
    threadPool.SetNumOfThreads(2);
    sleep(1);
    TestInt(voc, "SetNumOfThreads - decrease", 2, threadPool.GetNumOfThreads());
    sleep(6);
    TestInt(voc, "SetNumOfThread - unhindered", 800000, g_counter);
}