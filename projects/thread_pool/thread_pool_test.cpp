#include <iostream>

#include "thread_pool.hpp"
#include "utility.hpp"

using namespace ilrd;

class Task1: public ThreadPool::Task
{
	virtual void Run()
	{
		std::cout << "Task 1";
	}
};

class Task2: public ThreadPool::Task
{
	virtual void Run()
	{
		std::cout << "Task 2";
	}
};

class Task3: public ThreadPool::Task
{
	virtual void Run()
	{
		std::cout << "Task 3";
	}
};

static void ThreadPool1()
{
	boost::shared_ptr<Task1> task1(new Task1());
	boost::shared_ptr<Task2> task2(new Task2());
	boost::shared_ptr<Task3> task3(new Task3());

	ThreadPool tp(4);
	tp.Add(task3, ThreadPool::LOW);
	tp.Add(task1, ThreadPool::HIGH);
	tp.Add(task2, ThreadPool::MEDIUM);

	tp.Start();
}

int main()
{
	ThreadPool1();

	return 0;
}
