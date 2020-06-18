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
#include "protocol_consts.hpp"
#include "logger_preprocessor.hpp"

namespace ilrd
{

Master::Master(ConfigurationBase *config):
    m_config(config),
    m_framework(config),
    m_reactor(m_framework.Get<Reactor *>("reactor")),
    m_nbdCommunicator(m_config->Get("ILRD_NBD_PATH").c_str(), GetNumOfBlocks(), *m_reactor),
    m_minionCommunicator(m_config->Get("ILRD_MINION_PORT").c_str())
{
    m_nbdCommunicator.NBDSetUp();
    m_reactor->InsertFD(m_nbdCommunicator.GetMasterFD(), FDListener::READ, boost::bind(&Master::RequestCallback, this));
    m_reactor->InsertFD(m_minionCommunicator.GetMinionFD(), FDListener::READ, boost::bind(&Master::ReplyCallback, this));

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
    m_reactor->Run();
}

/******************************************************************************/

void Master::RequestCallback()
{
    std::cout << "\n****** Request Callback ******\n";
    ssize_t bytes_read = 0;
    struct nbd_request request;
    int fd = m_nbdCommunicator.GetMasterFD();
    
    if (0 >= (bytes_read = read(fd, &request, sizeof(request))))
    {
        throw details::ReadError();
    }

    std::cout << "request ID: " << *reinterpret_cast<uint64_t*>(request.handle) << "\n";

    assert(bytes_read == sizeof(request));
    assert(request.magic == htonl(NBD_REQUEST_MAGIC));

    std::cout << "bytes read: " << bytes_read << "\n";

    switch(be32toh(request.type)) 
    {

    case NBD_CMD_READ:
        std::cout << "Request for read of size: " << ntohl(request.len) << "\n";
        m_minionCommunicator.WriteRequest(request.type, request.from, request.handle);
        
        break;

    case NBD_CMD_WRITE:
        std::cout << "Request for write of size: " << ntohl(request.len) << "\n";
        std::cout << "request type value: " << be32toh(request.type) << "\n";
        std::size_t len = be32toh(request.len);
        char *chunk = new char[len];
        ReadAll(fd, chunk, len);
        m_minionCommunicator.WriteRequest(request.type, request.from, request.handle, chunk);
        
        delete[] chunk;
        break;
    }   
}

/******************************************************************************/

void Master::ReplyCallback()
{
    std::cout << "\n****** Reply Callback ******\n";
    struct nbd_reply reply;
    char *buffer = new char[protocol::BLOCK_SIZE + protocol::REPLY_METADATA_SIZE];

    m_minionCommunicator.ReadReply(buffer);
    u_int8_t type = buffer[0];
    
    std::cout << "request ID: " << *reinterpret_cast<uint64_t*>(buffer + 1) << "\n";

    InitReplyToNBD(reply, buffer);

    int fd = m_nbdCommunicator.GetMasterFD();

    std::cout << "type in reply: " << (int)type << "\n";
    WriteAll(fd, (char *)&reply, sizeof(struct nbd_reply));
    
    switch (type)
    {
    case 0:
        std::cout << "read reply\n";
        WriteAll(fd, buffer + protocol::READ_DATA_BLOCK_OFFSET, protocol::BLOCK_SIZE);
        delete[] buffer;
        break;

    case 1:
        std::cout << "write reply\n";
        delete[] buffer;
        break;
    }
}

/****************************** Private Functions *****************************/

void Master::WriteAll(int fd, char *buffer, std::size_t count)
{
    int bytes_written = 0;
    std::cout << "writeall count = " << count << "\n";
    while (count > 0) 
    {
        std::cout << "inside while in write all\n";
        if (0 >= (bytes_written = write(fd, buffer, count)))
        {
            throw details::WriteError();
        }
        
        buffer += bytes_written;
        count -= bytes_written;
        std::cout << "writeall bytes_written = " << bytes_written << "\n";
    }
    assert(count == 0);
    std::cout << "bytes written write all: " << bytes_written << "\n";  
}

/******************************************************************************/

void Master::ReadAll(int fd, char *buffer, std::size_t count)
{
    std::cout << "enter bytes read\n";
    int bytes_read = 0;
    while (count > 0) 
    {
        if (0 >= (bytes_read = read(fd, buffer, count)))
        {
            throw details::ReadError();
        }
        
        buffer += bytes_read;
        count -= bytes_read;
        std::cout << "readall bytes_read = " << bytes_read << "\n";
    }
    std::cout << "readall bytes_read : " << bytes_read << "\n";  
    assert(count == 0);    
}

/******************************************************************************/

void Master::InitReplyToNBD(struct nbd_reply& reply, const char *data)
{
    reply.magic = htonl(NBD_REPLY_MAGIC);
    memcpy(reply.handle, data + protocol::REQUEST_ID_OFFSET, sizeof(u_int64_t));
    reply.error = data[protocol::ERROR_CODE_OFFSET];
    std::cout << "reply error: " << reply.error << "\n";
}

/******************************************************************************/

std::size_t Master::GetNumOfBlocks() const
{
    return atoi(m_config->Get("ILRD_NUMBER_OF_4K_BLOCKS").c_str());
}

} // namespace ilrd


