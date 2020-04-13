#include <iostream>
#include "file.hpp"

using namespace ilrd;

int main()
{
    File f1("file1");
    f1.Display(1);
    Entry *e = new File("file2");
    File *f = dynamic_cast<File *>(e);
    
	return 0;
}
