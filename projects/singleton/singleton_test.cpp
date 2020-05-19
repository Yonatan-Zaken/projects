#include <cstdio>

#include "singleton.hpp"

using namespace ilrd;

int main()
{
	boost::mutex *s1 = Singleton<boost::mutex>::GetInstance();
	boost::mutex *s2 = Singleton<boost::mutex>::GetInstance();
	boost::mutex *s3 = Singleton<boost::mutex>::GetInstance();
	boost::mutex *s4 = Singleton<boost::mutex>::GetInstance();
	
	return 0;
}