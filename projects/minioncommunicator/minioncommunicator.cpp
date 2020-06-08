/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/
#include <inttypes.h>   // uintn_t

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

    m_client.SendTo(request);
    
    delete[] request;
    request = nullptr;
}

/******************************************************************************/

void MinionCommunicator::WriteRequest(u_int32_t requestType, u_int64_t blockOffset, char *requestID, const char *dataBlock)
{
    u_int8_t *request = new u_int8_t[protocol::BLOCK_SIZE + protocol::REQUEST_METADATA_SIZE];
    
    BuildRequestProtocol(requestType, blockOffset, requestID, reinterpret_cast<char *>(request));

    memcpy(request + protocol::WRITE_DATA_BLOCK_OFFSET, dataBlock, protocol::BLOCK_SIZE);

    m_client.SendTo(request);
 
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
    buffer[0] = requestType;
    memcpy(buffer + protocol::REQUEST_ID_OFFSET, requestID, sizeof(uint64_t));
    memcpy(buffer + protocol::BLOCK_ID_OFFSET, &blockOffset, sizeof(uint64_t));
}

/******************************************************************************/


} // namespace ilrd



