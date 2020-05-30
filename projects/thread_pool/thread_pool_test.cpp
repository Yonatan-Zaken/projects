#include <iostream>

#include "thread_pool.hpp"
#include "utility.hpp"

using namespace ilrd;

class UserTask: public ThreadPool::Task
{
public:
	explicit UserTask(int i): m_num(i) {}

	virtual void Run()
	{
		std::cout << boost::this_thread::get_id() << "Task " << m_num << "\n";
	}
private:
	int m_num;
};

class ExceptionTask: public ThreadPool::Task
{
public:
	virtual void Run()
	{
		std::cout << "task that throws exception\n";
		throw "Testing the logger";
	}
};

static void ThreadPool1()
{
	boost::shared_ptr<UserTask> task1(new UserTask(1));
	boost::shared_ptr<UserTask> task2(new UserTask(2));
	boost::shared_ptr<UserTask> task3(new UserTask(3));
	boost::shared_ptr<UserTask> task4(new UserTask(4));
	boost::shared_ptr<UserTask> task5(new UserTask(5));
	boost::shared_ptr<UserTask> task6(new UserTask(6));
	boost::shared_ptr<UserTask> task7(new UserTask(7));
	boost::shared_ptr<ExceptionTask> task8(new ExceptionTask());

	ThreadPool tp(4, boost::chrono::seconds(3));
	tp.Add(task1, ThreadPool::HIGH);
	tp.Add(task2, ThreadPool::MEDIUM);
	tp.Add(task3, ThreadPool::LOW);
	tp.Add(task4, ThreadPool::HIGH);
	tp.Add(task5, ThreadPool::LOW);
	tp.Add(task6, ThreadPool::MEDIUM);
	tp.Add(task7, ThreadPool::LOW);
	//tp.Add(task8, ThreadPool::MEDIUM);

	tp.Start();
	sleep(6);

	tp.SetNumOfThreads(2);
	sleep(3);
	
	/*
	tp.Add(task1, ThreadPool::HIGH);
	tp.Add(task2, ThreadPool::MEDIUM);
	tp.Add(task3, ThreadPool::LOW);
	sleep(2);
	std::cout << "num of threads: " << tp.GetNumOfThreads() << "\n";

	tp.Stop();

	tp.Pause();
	
	tp.Add(task1, ThreadPool::HIGH);
	tp.Add(task2, ThreadPool::MEDIUM);
	tp.Add(task3, ThreadPool::LOW);
	
	tp.Start();
	sleep(3);

	tp.Stop();
*/
}

int main()
{
	ThreadPool1();

	return 0;
}
