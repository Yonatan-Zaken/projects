/*******************************
    Yonatan Zaken
    Connection
    CPP
    ILRD - RD8081               
*******************************/
#include <cstring>  // memcpy
#include <endian.h> // htobe64

#include "connection.hpp"

namespace ilrd
{

Connection::Connection(const char* port, Reactor& reactor, callback_t callback):
    m_udp(UDPServer(port)),
    m_reactor(reactor),
    m_callback(callback)
{
    m_reactor.InsertFD(GetFD(), FDListener::READ, m_callback);
}

/******************************************************************************/

Connection::~Connection() noexcept
{
    m_reactor.RemoveFD(GetFD(), FDListener::READ);
}

/******************************************************************************/

int Connection::GetFD() const noexcept
{
    return m_udp.GetFD();
}

/******************************************************************************/

boost::shared_ptr<Message> Connection::ConstructRequest() 
{
    uint8_t buffer[details::RECV_BLOCK_SIZE] = {0};
    m_udp.ReceiveFrom(buffer);

    uint8_t requestType = buffer[details::OPERATION_TYPE_OFFSET];
    uint64_t requestID = *(reinterpret_cast<uint64_t *>(buffer + details::REQUEST_ID_OFFSET));
    uint64_t blockID = *(reinterpret_cast<uint64_t *>(buffer + details::BLOCK_ID_OFFSET));
    
    switch(requestType)
    {
        case 0:
        {
            boost::shared_ptr<Message> readReq(new RequestRead(requestType, be64toh(requestID), be64toh(blockID)));

            return readReq;
        }
            
        case 1:
        {
            boost::shared_ptr<Message> writeReq(new RequestWrite(
            requestType, be64toh(requestID), be64toh(blockID), buffer + details::WRITE_DATA_BLOCK_OFFSET));

            return writeReq;
        } 
    } // switch-case
}

/******************************************************************************/

void Connection::SendMessage(boost::shared_ptr<Message> reply) 
{
    uint8_t replyType = reply->GetOperation();
    uint8_t errorCode = reply->GetStatusCode();
    uint64_t requestId = htobe64(reply->GetID());

    switch (replyType)
    {
    case 0:
    {
        uint8_t buffer[details::REPLY_READ_SIZE] = {0};
        
        buffer[details::OPERATION_TYPE_OFFSET] = replyType;
        
        memcpy(buffer + details::REQUEST_ID_OFFSET, &requestId, sizeof(uint64_t));
        
        buffer[details::ERROR_CODE_OFFSET] = errorCode;
        memcpy(buffer + details::READ_DATA_BLOCK_OFFSET, reply->DataBlock(), details::BLOCK_SIZE);

        m_udp.SendTo(buffer);
        break;
    }
    
    case 1:
    {
        uint8_t buffer[details::REPLY_WRITE_METADATA_SIZE] = {0};

        buffer[details::OPERATION_TYPE_OFFSET] = replyType;
        
        memcpy(buffer + details::REQUEST_ID_OFFSET, &requestId, sizeof(uint64_t));
        
        buffer[details::ERROR_CODE_OFFSET] = errorCode;

        m_udp.SendTo(buffer);
        break;
    }
    } // switch-case
}

} // namespace ilrd


