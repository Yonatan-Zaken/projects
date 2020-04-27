#include <iostream>
#include <cstdio>
#include <dlist.hpp>
#include <point.hpp>
#include <simplestring.hpp>
#include <cstring>

using namespace ilrd;

#define LOOP 3
#define BUFFSIZE 500

static void DListTest1()
{
	std::cout << "DList Test1 int\n\n";

	DList<int> d1;
	RUN_TEST(0 == d1.Size(), "size");
	RUN_TEST(1 == d1.IsEmpty(), "isempty");

	for (int i = 0; i < LOOP; i++)
	{
		d1.PushBack(i);
		RUN_TEST(i == d1.PeekBack(), "peekback + pushback");
	}
	
	RUN_TEST(0 == d1.IsEmpty(), "isempty");
	RUN_TEST(LOOP == d1.Size(), "size");

	for (int i = LOOP - 1; i >= 0; --i)
	{
		RUN_TEST(i == d1.PopBack(), "popback");
	}
	
	for (int i = 0; i < LOOP; ++i)
	{
		d1.PushFront(i);
		RUN_TEST(i == d1.PeekFront(), "peekfront + pushfornt");
	}

	RUN_TEST(0 == d1.IsEmpty(), "isempty");
	RUN_TEST(LOOP == d1.Size(), "size");
	
	DList<int> d2(d1);


	for (int i = 0; i < LOOP; ++i)
	{
		RUN_TEST(d1.PopFront() == d2.PopFront(), "ctor + popfront");
	}
	
	for (int i = 0; i < LOOP; i++)
	{
		d1.PushBack(i);
	}

	d2 = d1;

	for (int i = 0; i < LOOP; ++i)
	{
		RUN_TEST(d1.PopFront() == d2.PopFront(), "operator= + popfront");
	}
	

	std::cout << "\n\n";
}

static void DListTest2()
{
	std::cout << "DList Test2 Point Class\n\n";

	DList<Point> d1;
	for (size_t i = 0; i < LOOP; ++i)
	{
		d1.PushBack(Point(i,i+15));
		std::cout << d1.PeekBack().GetX() << "," << d1.PeekBack().GetY() <<" pushback + peekback\n";
	}
	RUN_TEST(LOOP == d1.Size(), "size");

	DList<Point> d2(d1);
	for (size_t i = 0; i < LOOP; ++i)
	{
		std::cout << d2.PeekBack().GetX() << "," << d2.PeekBack().GetY() <<" ctor\n";
	}
	
	for (size_t i = 0; i < LOOP; ++i)
	{
		d1.PopBack();
	}
	RUN_TEST(0 == d1.Size(), "popback");

	d1 = d2;

	for (size_t i = 0; i < LOOP; ++i)
	{
		RUN_TEST(d1.PeekFront() == d2.PeekFront(), "peekfront + operator=");
	}

	std::cout << "\n\n";
}

static void DListTest3()
{
    char buffer[BUFFSIZE] = {0};
	DList<String> d1;
    
    for (int i = 0; i < LOOP; ++i)
    {
        d1.PushBack(strcat(buffer, "WOLSELEY"));
        std::cout << d1.PeekBack() << " pushback + peekback\n";
    }
    
    DList<String> d2(d1);
    
    for (int i = 0; i < LOOP; ++i)
    {
        RUN_TEST(d2.PopFront() == d1.PopFront(), "ctor + popfront");
    }

	DList<String> d3;

	d3.PushBack(String("hello"));

	d1 = d2 = d3;

	RUN_TEST(d1.PeekBack() == d3.PeekBack(), "chaining d1 = d2 = d3");
}

static void DListTest4()
{
	DList<char> d1;
	try
	{
		d1.PopBack();	
	}
	catch(const std::string& e)
	{
		std::cerr << e << '\n';
	}
}

int main()
{
	DListTest1();
	DListTest2();
	DListTest3();
	DListTest4();

	return 0;
}
