#include <iostream>
#include <cstdio>
#include <cstring>

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
	RUN_TEST(1 == (b1 == b2), "operator==  + set");
	b3.Set(5);
	b3.Set(16);
	b3.Set(20);
	RUN_TEST(1 == (b3 != b2), "operator!=");
	b1.SetVal(16, 1);
	RUN_TEST(1 == b1.IsOn(16), "is on + set val");
	RUN_TEST(0 == b1.IsOff(16), "is off");
	b1.SetVal(16, 0);
	b1.SetVal(16,0);
	RUN_TEST(2 == b1.CountOn(), "count on");
	RUN_TEST(18 == b1.CountOff(), "count off");
	b1.FlipAll();
	b1.Reset(17);
	b1.SetAll();
	RUN_TEST(20 == b1.CountOn(), "count on + set all");
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
	cout << "Bitset test 2\n\n";

	BitSet<24> b1("111100110100000100000101");
	b1.SetAll();
	RUN_TEST(24 == b1.CountOn(), "set all");
	b1.Flip(8);
	RUN_TEST(0 == b1.Get(8), "get");

	BitSet<19> b2("0110111011111110000");
	b2.FlipAll();
	RUN_TEST(12 == b2.CountOff(), "count off + flip all");
	RUN_TEST(12 == (~b2).CountOn(), "operator~");
	RUN_TEST(1 == (b2.Reset(5)).IsOff(5), "reset + is off");


	cout << "\n\n";
}

static void BitSetTest3()
{
	cout << "Bitset test 3\n\n";

	BitSet<8> b1("11110000");
	BitSet<8> b2("00001111");

	b1 &= b2;
	b1 |= b2;
	b1 ^= b2;

	RUN_TEST((BitSet<8>("00000000") == (b1 &= b2)), "operator &=");
	RUN_TEST((BitSet<8>("00001111") == (b1 |= b2)), "operator |=");
	RUN_TEST((BitSet<8>("00000000") == (b1 ^= b2)), "operator ^=");
	
	BitSet<14> b3("10000000001001");
	BitSet<14> b4("00000000000110");

	RUN_TEST((BitSet<14>("10000000001111") == (b3 |= b4)), "operator |=");
	RUN_TEST((BitSet<14>("00000000000110") == (b3 &= b4)), "operator &=");
	RUN_TEST((BitSet<14>("00000000000000") == (b3 ^= b4)), "operator ^=");

	BitSet<24> b5("111100000000111100000011");
	BitSet<24> b6("000000110000011000000001");
	BitSet<24> b7;
	b7 = b5 | b6;
	RUN_TEST(BitSet<24>("111100110000111100000011") == b7, "operator|");
	b7 = b5 & b6;
	RUN_TEST(BitSet<24>("000000000000011000000001") == b7, "operator&");
	b7 = b5 ^ b6;
	RUN_TEST(BitSet<24>("111100110000100100000010") == b7, "operator^");
	
	RUN_TEST(b7.ToString() == ("111100110000100100000010"), "to string");

	BitSet<19> b8;
	(b8.Set(19)).Set(13).Set(8).Set(1);
	RUN_TEST(b8.ToString() == ("000001000001000010000001"), "to string");
	cout << b2 << " [ostream]\n";
	cout << b8 << " [ostream]\n";

	b2[8] = 1;
	RUN_TEST(1 == b2.IsOn(8), "operator[]");
	cout << b2 << " [ostream]\n";
	cout << b2[5] << " operator []\n";
	b2[7] = b2[6] = b2[1];
	RUN_TEST(1 == b2.IsOn(7), "chaining operator[]");
	RUN_TEST(1 == b2.IsOn(6), "chaining operator[]");
	cout << b2 << " [ostream]\n";

	cout << "\n\n";
}

static void BitSetTest4()
{
	cout << "Bitset test 4\n\n";

	BitSet<12> b1("111000111000");
	std::fill(b1.Begin(), b1.End(), 0);
	cout << b1 << " [iterator]\n";
	std::fill(b1.Begin(), b1.End(), 1);
	cout << b1 << " [iterator]\n";

	BitSet<12> b2("111000111000");

	b1.End() - 1;
	b1.Begin() + 1;
	cout << "\n\n";

	b2 >>= 2;
	cout << b2 << "\n";

	b2 = b2 >> 2;
	cout << b2 << "\n";

	b2 <<= 7;
	cout << b2 << "\n";

	b2 = b2 >> 7;
	cout << b2 << "\n";

	BitSet<18> b3("111010001110101100");
	cout << b3 << "\n";
	b3 >>= 10;
	cout << b3 << "\n";
	RUN_TEST(("000000000000000011101000") == b3.ToString(), "operator>>=");

	

}

int main()
{
	BitsetTest1();
	BitSetTest2();
	BitSetTest3();
	BitSetTest4();

	return 0;
}
