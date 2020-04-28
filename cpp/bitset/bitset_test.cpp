#include <iostream>
#include <cstdio>

#include "utility.hpp"
#include "bitset.hpp"

using namespace std;
using namespace ilrd;

static void BitsetTest1()
{
	cout << "Bitset test 1\n\n";
	
	BitSet<20> b1;
	BitSet<20> b2;
	BitSet<20>b3;
	RUN_TEST(0 == b1.CountOn(), "count on");
	RUN_TEST(20 == b1.CountOff(), "count off");
	b1.Set(17);
	b1.Set(20);
	b2.Set(17);
	b2.Set(20);
	RUN_TEST(1 == (b1 == b2), "operator==");
	b3.Set(5);
	b3.Set(16);
	b3.Set(20);
	RUN_TEST(1 == (b3 != b2), "operator!=");
	b1.SetVal(16, 1);
	RUN_TEST(1 == b1.IsOn(16), "is on");
	RUN_TEST(0 == b1.IsOff(16), "is off");
	b1.SetVal(16, 0);
	b1.SetVal(16,0);
	RUN_TEST(2 == b1.CountOn(), "count on");
	RUN_TEST(18 == b1.CountOff(), "count off");
	b1.FlipAll();
	b1.Reset(17);
	b1.SetAll();
	RUN_TEST(20 == b1.CountOn(), "count on");
	b1.ResetAll();
	b2.ResetAll();
	RUN_TEST(1 == (b1 == b2), "operator==");
	RUN_TEST(1 == b3.Get(5), "get");
	RUN_TEST(1 == b3.Get(16), "get");
	try
	{
		b3.Get(21);
	}
	catch(const std::out_of_range& e)
	{
		DEBUG(e.what());
	}
	try
	{
		b3.Get(-1);
	}
	catch(const std::out_of_range& e)
	{
		DEBUG(e.what());
	}

	cout << "\n\n";
}

static void BitSetTest2()
{
	BitSet<16> b1("0100000100000101");
	
}

int main()
{
	BitsetTest1();
	BitSetTest2();

	return 0;
}
