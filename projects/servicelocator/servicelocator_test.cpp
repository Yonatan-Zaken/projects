#include <iostream>
#include <cstdio>
#include <string>

#include "thread_pool.hpp"
#include "reactor.hpp"
#include "servicelocator.hpp"

using namespace ilrd;

static void ServiceLocatorTest1()
{
	ServiceLocator<std::string> s1;

	Reactor r1;
	s1.Add<Reactor *>("reactor", &r1);
	Reactor *r2 = s1.Get<Reactor *>("reactor");
	
	ThreadPool t1(4, boost::chrono::seconds(3));
	s1.Add<ThreadPool *>("threadpool", &t1);
	ThreadPool *t2 = s1.Get<ThreadPool *>("threadpool");

	RUN_TEST(4 == t2->GetNumOfThreads(), "get num of threads");
	t2->SetNumOfThreads(7);
	RUN_TEST(7 == t2->GetNumOfThreads(), "set num of threads");
}

int main()
{
	ServiceLocatorTest1();

	return 0;
}
