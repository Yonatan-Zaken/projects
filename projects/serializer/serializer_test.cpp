#include <iostream>
#include <sstream> 
#include "circle.hpp"
#include "serializer.hpp"

using namespace ilrd;

int main()
{
	std::stringbuf buffer;
	std::ostream os(&buffer);
	std::istream is(&buffer);

	Circle c1(Point(50, 90), COLOR_BLUE, 20);
	
	Serializer<Shape> s1;
	s1.Add<Circle>(&Circle::CreateCircle);

	s1.Serialize(c1, os);
	s1.Deserialize(is);

	return 0;
}
