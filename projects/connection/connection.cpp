/*******************************
    Yonatan Zaken
    Connection
    CPP
    ILRD - RD8081               
*******************************/
#include <cstring>  // memcpy
#include <endian.h> // htobe64

#include "connection.hpp"
#include "protocol_consts.hpp"

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
    uint8_t buffer[protocol::RECV_BLOCK_SIZE] = {0};
    m_udp.ReceiveFrom(buffer);

    uint8_t requestType = buffer[protocol::OPERATION_TYPE_OFFSET];
    uint64_t requestID = *(reinterpret_cast<uint64_t *>(buffer + protocol::REQUEST_ID_OFFSET));
    uint64_t blockID = *(reinterpret_cast<uint64_t *>(buffer + protocol::BLOCK_ID_OFFSET));
    
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
            requestType, be64toh(requestID), be64toh(blockID), buffer + protocol::WRITE_DATA_BLOCK_OFFSET));

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
        uint8_t buffer[protocol::REPLY_READ_SIZE] = {0};
        
        buffer[protocol::OPERATION_TYPE_OFFSET] = replyType;
        
        memcpy(buffer + protocol::REQUEST_ID_OFFSET, &requestId, sizeof(uint64_t));
        
        buffer[protocol::ERROR_CODE_OFFSET] = errorCode;
        memcpy(buffer + protocol::READ_DATA_BLOCK_OFFSET, reply->DataBlock(), protocol::BLOCK_SIZE);

        m_udp.SendTo(buffer);
        break;
    }
    
    case 1:
    {
        uint8_t buffer[protocol::REPLY_WRITE_METADATA_SIZE] = {0};

        buffer[protocol::OPERATION_TYPE_OFFSET] = replyType;
        
        memcpy(buffer + protocol::REQUEST_ID_OFFSET, &requestId, sizeof(uint64_t));
        
        buffer[protocol::ERROR_CODE_OFFSET] = errorCode;

        m_udp.SendTo(buffer);
        break;
    }
    } // switch-case
}

} // namespace ilrd


