#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "storage.hpp"

using namespace ilrd;

int main()
{
	char data[30] = "Give me my data back";
	char data2[57] = "ssssssssssssssssssssssssssssssssssssssssssssssssssssssss";
	size_t arr[7] = {1,2,3,4,5,6,7};
	char *str = (char*)arr;
	
	HeapStorage h1(4);

	h1.Write(data, 3);
	RUN_TEST(0 == strcmp(h1.Read(3), "Give me my data back"), "storage");

	h1.Write(data2, 0);
	RUN_TEST(0 == strcmp(h1.Read(0), "ssssssssssssssssssssssssssssssssssssssssssssssssssssssss"), "storage");
	
	h1.Write(str, 1);
	RUN_TEST(7 == *(size_t*)h1.Read(1) + 6, "storage");
	
	int fd = open("/home/yonatan10/storage_test", O_RDONLY);
	char buff[h1.blockSize];
	read(fd, buff, h1.blockSize);

	h1.Write(buff, 0);
	

	close(fd);


	return 0;
}
