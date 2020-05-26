#include <iostream>
#include <cstdio>
#include <sstream>
#include <boost/bind.hpp>

#include "serializer.hpp"
#include "circle.hpp"

using namespace ilrd;

int main()
{
	std::stringbuf buffer;
	std::ostream os(&buffer);
	std::istream is(&buffer);

	Circle c1(Point(50, 90), COLOR_BLUE, 20);
	
	Serializer<Shape> s1;
	
	s1.Add<Circle>(CreateCircle);

	s1.Serialize(c1, os);

	boost::shared_ptr<Shape> basePtr(s1.Deserialize(is));

	RUN_TEST(basePtr->GetPosition().GetX() == 50, "x position");
	RUN_TEST(basePtr->GetPosition().GetY() == 90, "y position");
	RUN_TEST(basePtr->GetAngle() == 0, "angle test");

	return 0;
}
