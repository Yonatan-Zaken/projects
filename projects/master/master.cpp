/*********************
    Master
    CPP File
    01/06/2020
    ILRD - RD8081           
*********************/

#include <cassert>      // assert
#include <iostream>     // std::cout
#include <arpa/inet.h>  // htonl
#include <inttypes.h>   // be64toh

#include <boost/bind.hpp>

#include "master.hpp"
#include "logger_preprocessor.hpp"

namespace ilrd
{

Master::Master(const char *dev, std::size_t nbdSize, std::size_t storageSize):
    m_reactor(),
    m_storage(new char[storageSize]),
    m_communicator(dev, nbdSize, m_reactor, boost::bind(&Master::Callback, this))
{
    m_communicator.Start();
}

/******************************************************************************/

Master::~Master() noexcept
{
    delete[] m_storage;
}

/******************************************************************************/

void Master::Callback()
{
    ssize_t bytes_read = 0;
    struct nbd_request request;
    struct nbd_reply reply;
 
    int fd = m_communicator.GetMasterFD();
    
    if (-1 == (bytes_read = read(fd, &request, sizeof(request))))
    {
        throw details::ReadError();
    }
    std::cout << "bytes read: " << bytes_read << "\n";

    assert(bytes_read == sizeof(request));
    memcpy(reply.handle, request.handle, sizeof(reply.handle));
    reply.magic = htonl(NBD_REPLY_MAGIC);
    reply.error = htonl(0);
    
    u_int32_t len = ntohl(request.len);
    u_int64_t from = be64toh(request.from);
    assert(request.magic == htonl(NBD_REQUEST_MAGIC));

    switch(ntohl(request.type)) 
    {

    case NBD_CMD_READ:
        std::cout << "Request for read of size: " << len << "\n";
        void *chunk = operator new(len);  
        memcpy(chunk, m_storage + from, len);
        
        WriteAll(fd, (char *)&reply, sizeof(struct nbd_reply));
        WriteAll(fd, static_cast<char *>(chunk), len);

        operator delete(chunk);
        break;

    case NBD_CMD_WRITE:
        std::cout << "Request for write of size: " << len << "\n";
        void *chunk = operator new(len);
        ReadAll(fd, static_cast<char *>(chunk), len);
        memcpy(m_storage + from, chunk, len);
        
        operator delete(chunk);
        WriteAll(fd, (char *)&reply, sizeof(struct nbd_reply));
        break;
    }   
}

/****************************** Private Functions *****************************/

void Master::WriteAll(int fd, char *buffer, std::size_t count)
{
    int bytes_written = 0;

    while (count > 0) 
    {
        if (-1 == (bytes_written = write(fd, buffer, count)))
        {
            throw details::WriteError();
        }
        
        buffer += bytes_written;
        count -= bytes_written;
    }
    assert(count == 0);  
}

/******************************************************************************/

void Master::ReadAll(int fd, char *buffer, std::size_t count)
{
    int bytes_read = 0;

    while (count > 0) 
    {
        if (-1 == (bytes_read = read(fd, buffer, count)))
        {
            throw details::ReadError();
        }
        
        buffer += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);    
}

} // namespace ilrd


