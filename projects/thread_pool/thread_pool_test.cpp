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
		std::cout << "Task " << m_num << "\n";
	}
private:
	int m_num;
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

	ThreadPool tp(4);
	tp.Add(task1, ThreadPool::HIGH);
	tp.Add(task2, ThreadPool::MEDIUM);
	tp.Add(task3, ThreadPool::LOW);
	tp.Add(task4, ThreadPool::HIGH);
	tp.Add(task5, ThreadPool::LOW);
	tp.Add(task6, ThreadPool::MEDIUM);
	tp.Add(task7, ThreadPool::LOW);

	tp.Start();
}

int main()
{
	ThreadPool1();

	return 0;
}