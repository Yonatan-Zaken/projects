#include <iostream>
#include <string>
#include "factory.hpp"

using namespace ilrd;

class Animal
{
public:
	virtual int GetNumLegs() const noexcept = 0;
};

class Cat: public Animal
{
public:
	explicit Cat(int numLegs): m_legs(numLegs) {}
	virtual int GetNumLegs() const noexcept {return m_legs;}

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
	virtual int GetNumLegs() const noexcept {return m_legs;}
	std::string GetVoice() const noexcept {return m_voice;}

private:
	int m_legs;
	std::string m_voice;
};

struct Param
{
	int m_numLegs;
	std::string m_voice;
};

Cat *CreateCat(const Param& param)
{
	return (new Cat(param.m_numLegs));
}

Dog *CreateDog(const Param& param)
{
	return (new Dog(param.m_numLegs, param.m_voice));
}

static void FactoryTest1()
{
	Param cat;
	cat.m_numLegs = 4;
	Param dog;
	dog.m_numLegs = 6;
	dog.m_voice = "wrof!";

	Factory<Animal, std::string, Param> factory;
	factory.AddRecipe("cat", &CreateCat);
	factory.AddRecipe("dog", &CreateDog);

	Animal *animal = factory.Fabricate("dog", dog);
	std::cout << "num of legs: " << animal->GetNumLegs() << "\n";
	std::cout << "void: " << animal->GetVoice() << "\n";

	Animal *animal2 = factory.Fabricate("cat", cat);
	std::cout << "num of legs: " << animal2->GetNumLegs() << "\n";
}

int main()
{
	FactoryTest1();

	return 0;
}
