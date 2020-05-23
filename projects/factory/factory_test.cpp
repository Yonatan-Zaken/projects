#include <iostream>
#include <string>
#include "factory.hpp"
using namespace ilrd;

class Animal
{
public:
	virtual int GetNumLegs() const noexcept = 0;
}

class Cat: public Animal
{
public:
	explicit Cat(int numLegs): m_legs(numLegs) {}
	virtual int GetNumLegs() {return m_legs;}
private:
	int m_legs;
};

class Dog: public Animal
{
public:
	explicit Dog(int numLegs, std::string voice):
	m_legs(numLegs),
	m_voice(voice)
	{}
	virtual int GetNumLegs() {return m_legs;}
	std::string GetVoice() {return m_voice;}
private:
	int m_legs;
	std::string m_voice;
};

static void FactoryTest1()
{
	
}

int main()
{
	FactoryTest1();

	return 0;
}
