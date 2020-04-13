#include <iostream>

#include "directory.hpp"
#include "file.hpp"

using namespace ilrd;

int main()
{
    Directory d1("sub_root");
    Directory d2("dir1");    
    Directory d3("dir2");
    File f1("file1");
    File f2("file2");
    
    Entry *e1 = &d2;
    Entry *e2 = &d3;
    Entry *e3 = &f1;
    Entry *e4 = &f2;
    
    d1.AddEntry(e1);
    d1.AddEntry(e2);
    d1.AddEntry(e3);
    d1.AddEntry(e4);
    
    Entry *e5 = &d1;
    
    Directory d4("root");
    File f3("file3");
    File f4("file4");
    
    Entry *e6 = &f3;
    Entry *e7 = &f4;
    
    d4.AddEntry(e5);
    d4.AddEntry(e6);
    d4.AddEntry(e7);
    
    d4.Display(0);
    
	return 0;
}
