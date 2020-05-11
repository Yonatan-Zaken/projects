#include <iostream>
#include <boost/bind.hpp>

#include "reactor.hpp"

extern "C"
{
	#include "socket.h"
}

using namespace ilrd;

void print1()
{
	std::cout << "print1\n";
}

void Accept(Reactor *r_, int fd)
{
    struct sockaddr_storage remoteaddr = {0}; 
    socklen_t addrlen = {0};
    int newfd = 0;        
    char remoteIP[INET_ADDRSTRLEN] = {0};
	fd_set empty;

    addrlen = sizeof(remoteaddr);
    newfd = accept(fd, (struct sockaddr *)&remoteaddr, &addrlen);
    if (-1 == newfd) 
    {      
    } 
    else 
    {
        r_->InsertFD(newfd, FDListener::READ, boost::bind(TCPDataTransfer,newfd, &empty)); 
    }
}

void Read()
{
	char buf[20] = {0};
	read(STDIN_FILENO, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, strlen(buf));
}

static void ReactorTest1()
{
	int fd = 0;
	struct addrinfo hints = {0};
	fd_set empty; 
	InitHints(&hints, AF_INET, SOCK_STREAM, AI_PASSIVE);
	fd = GetSocket("y10", "4443", &hints, TCP, SERVER);
	listen(fd, 10);

	Reactor r1;
	r1.InsertFD(fd, FDListener::READ, boost::bind(Accept, &r1, fd));
	/*r1.InsertFD(fd, FDListener::READ, boost::bind(UDPDataTransfer, fd));*/
	
	/*r1.InsertFD(0, FDListener::READ, Read);*/

	try
	{
		r1.Run();
	}
	catch(const std::exception& e)
	{
		e.what();
	}
}

int main()
{
	ReactorTest1();
	
	return 0;
}
