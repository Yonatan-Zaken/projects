/*********************
    Minion Communicator
    CPP File
    01/06/2020
    ILRD - RD8081           
*********************/
#include <inttypes.h>   // uintn_t
#include <iostream>
#include <arpa/inet.h>  // htonl

#include "protocol_consts.hpp"
#include "minioncommunicator.hpp"

namespace ilrd
{

MinionCommunicator::MinionCommunicator(const char *port):
    m_client(port),
    m_minionFD(m_client.GetFD())
{
}

/******************************************************************************/

MinionCommunicator::~MinionCommunicator() noexcept
{
}

/******************************************************************************/

void MinionCommunicator::WriteRequest(u_int32_t requestType, u_int64_t blockOffset, char *requestID)
{
    u_int8_t *request = new u_int8_t[protocol::REQUEST_METADATA_SIZE];
    
    BuildRequestProtocol(requestType, blockOffset, requestID, reinterpret_cast<char *>(request));

    std::cout << "request type: " << requestType << "\n";
    std::cout << "request ID: " << requestID << "\n";
    std::cout << "request Block ID: " << ntohl(blockOffset) / 4096 << "\n";

    m_client.SendTo(request);
    
    delete[] request;
    request = nullptr;
}

/******************************************************************************/

void MinionCommunicator::WriteRequest(u_int32_t requestType, u_int64_t blockOffset, char *requestID, const char *dataBlock)
{
    std::cout << "enter write request requestType = " << be32toh(requestType) << "\n";
    u_int8_t *request = new u_int8_t[protocol::BLOCK_SIZE + protocol::REQUEST_METADATA_SIZE];
    
    BuildRequestProtocol(requestType, blockOffset, requestID, reinterpret_cast<char *>(request));

    memcpy(request + protocol::WRITE_DATA_BLOCK_OFFSET, dataBlock,protocol::BLOCK_SIZE);

    std::cout << "before sendto\n";
    m_client.SendTo(request);
    std::cout << "after sendto\n";

    delete[] request;
    request = nullptr;
}

/******************************************************************************/

void MinionCommunicator::ReadReply(char *buffer)
{
    m_client.ReceiveFrom(reinterpret_cast<u_int8_t *>(buffer));
}

/******************************************************************************/

void MinionCommunicator::BuildRequestProtocol(u_int32_t requestType, u_int64_t blockOffset, char *requestID, char *buffer)
{
    buffer[0] = be32toh(requestType);
    memcpy(buffer + protocol::REQUEST_ID_OFFSET, requestID, sizeof(uint64_t));
    
    blockOffset = htobe64(be64toh(blockOffset) / protocol::BLOCK_SIZE);
    memcpy(buffer + protocol::BLOCK_ID_OFFSET, &blockOffset, sizeof(uint64_t));
}

/******************************************************************************/

} // namespace ilrd



