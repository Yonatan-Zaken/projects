#include <iostream>
#include <cstdio>
#include <unistd.h>        
#include <sys/inotify.h>    // inotify_init
#include <linux/limits.h>   // NAME_MAX

#include "inotify.hpp"
#include "utility.hpp"

using namespace ilrd;

static void InotifyTest()
{
	Inotify i1("/home/yonatan10/dir1");

	const struct inotify_event *event = nullptr;
	char buffer[sizeof(struct inotify_event) + NAME_MAX + 1] = {0};
	read(i1.GetFD(), buffer, sizeof(struct inotify_event) + NAME_MAX + 1);

	event = (const struct inotify_event *)buffer;

	std::cout << "operation mask: " << event->mask << "\n";
	std::cout << "file name: " << event->name << "\n";

}

int main()
{
	InotifyTest();

	return 0;
}
