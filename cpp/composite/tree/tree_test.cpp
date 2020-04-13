#include <iostream>
#include "tree.hpp"

using namespace ilrd;

int main(int argc, char *argv[])
{
    UNUSED(argc);
    Tree t(argv[1]);
    Tree t2(t);
    t.Print();
    t2.Print();
	return 0;
}
