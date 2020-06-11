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

Master::Master(const char *dev, std::size_t nbdSize, const char *minionPort):
    m_reactor(),
    m_nbdCommunicator(dev, nbdSize, m_reactor),
    m_minionCommunicator(minionPort)
{
    m_nbdCommunicator.NBDSetUp();
    m_reactor.InsertFD(m_nbdCommunicator.GetMasterFD(), FDListener::READ, boost::bind(&Master::RequestCallback, this));
    m_reactor.InsertFD(m_minionCommunicator.GetMinionFD(), FDListener::READ, boost::bind(&Master::ReplyCallback, this));

    std::cout << "nbd fd" << m_nbdCommunicator.GetMasterFD() << "\n";
    std::cout << "minion fd" << m_minionCommunicator.GetMinionFD() << "\n";

}

/******************************************************************************/

Master::~Master() noexcept
{
}

/******************************************************************************/

void Master::StartNBDCommunication()
{
    m_reactor.Run();
}

/******************************************************************************/

void Master::RequestCallback()
{
    ssize_t bytes_read = 0;
    struct nbd_request request;
    int fd = m_nbdCommunicator.GetMasterFD();
    
    if (-1 == (bytes_read = read(fd, &request, sizeof(request))))
    {
        throw details::ReadError();
    }

    assert(bytes_read == sizeof(request));
    assert(request.magic == htonl(NBD_REQUEST_MAGIC));

    std::cout << "bytes read: " << bytes_read << "\n";
    std::cout << "request type: " << request.type << "\n";
    std::cout << "request ID: " << request.handle << "\n";
    std::cout << "request Block ID: " << request.from << "\n";

    //u_int32_t type = ntohl(request.type);
    //u_int32_t len = ntohl(request.len);
    //u_int64_t from = be64toh(request.from);

    switch(request.type) 
    {

    case NBD_CMD_READ:
        std::cout << "Request for read of size: " << ntohl(request.len) << "\n";
        m_minionCommunicator.WriteRequest(request.type, request.from, request.handle);
        
        break;

    case NBD_CMD_WRITE:
        std::cout << "Request for write of size: " << ntohl(request.len) << "\n";
        char *chunk = new char[request.len];
        ReadAll(fd, chunk, request.len);
        m_minionCommunicator.WriteRequest(request.type, request.from, request.handle, chunk);
        
        delete[] chunk;
        break;
    }   
}

/******************************************************************************/

void Master::ReplyCallback()
{
    struct nbd_reply reply;
    char *buffer = new char[protocol::BLOCK_SIZE + protocol::REPLY_METADATA_SIZE];

    m_minionCommunicator.ReadReply(buffer);
    u_int8_t type = buffer[0];
    
    InitReplyToNBD(reply, buffer);

    int fd = m_nbdCommunicator.GetMasterFD();
    WriteAll(fd, (char *)&reply, sizeof(struct nbd_reply));

    switch (type)
    {
    case 0:
        WriteAll(fd, buffer + protocol::READ_DATA_BLOCK_OFFSET, protocol::BLOCK_SIZE);
        delete[] buffer;
        
        break;

    case 1:
        delete[] buffer;

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

/******************************************************************************/

void Master::InitReplyToNBD(struct nbd_reply& reply, const char *data)
{
    reply.magic = htonl(NBD_REPLY_MAGIC);
    memcpy(reply.handle, data + protocol::REQUEST_ID_OFFSET, sizeof(u_int64_t));
    reply.error = 0;
    //reply.error = data[protocol::ERROR_CODE_OFFSET];
}

} // namespace ilrd


