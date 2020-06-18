/*******************************
    Yonatan Zaken
    Connection
    CPP
    ILRD - RD8081               
*******************************/
#include <cstring>  // memcpy
#include <endian.h> // htobe64
#include <iostream>
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

boost::shared_ptr<RequestMessage> Connection::ConstructRequest() 
{
    uint8_t buffer[protocol::RECV_BLOCK_SIZE] = {0};
    //uint8_t *buffer =  new uint8_t[protocol::RECV_BLOCK_SIZE];
    m_udp.ReceiveFrom(buffer);

    std::cout << "requestType: " << (int)(buffer[0]) << "\n";

    uint8_t requestType = buffer[protocol::OPERATION_TYPE_OFFSET];
    uint64_t requestID;
    memcpy(&requestID, buffer + protocol::REQUEST_ID_OFFSET, sizeof(uint64_t));
    //uint64_t requestID = *(reinterpret_cast<uint64_t *>(buffer + protocol::REQUEST_ID_OFFSET));
    uint64_t blockID;
    memcpy(&blockID, buffer + protocol::BLOCK_ID_OFFSET, sizeof(uint64_t));
    //uint64_t blockID = *(reinterpret_cast<uint64_t *>(buffer + protocol::BLOCK_ID_OFFSET));

    boost::shared_ptr<RequestMessage> request(new RequestMessage(requestType, be64toh(requestID), (be64toh(blockID)), buffer + protocol::WRITE_DATA_BLOCK_OFFSET));


    return request;
}

/******************************************************************************/

void Connection::SendMessage(boost::shared_ptr<ReplyMessage> reply) 
{
    uint8_t replyType = reply->GetOperation();
    uint8_t errorCode = reply->GetStatusCode();
    uint64_t requestId = htobe64(reply->GetID());

    std::cout << "replyType: " << (int)replyType << "\n";

    uint8_t buffer[protocol::REPLY_READ_SIZE] = {0};
    
    buffer[protocol::OPERATION_TYPE_OFFSET] = replyType;    
    memcpy(buffer + protocol::REQUEST_ID_OFFSET, &requestId, sizeof(uint64_t));
    buffer[protocol::ERROR_CODE_OFFSET] = errorCode;

    memcpy(buffer + protocol::READ_DATA_BLOCK_OFFSET, reply->DataBlock(), protocol::BLOCK_SIZE);

    m_udp.SendTo(buffer);
}

/******************************************************************************/
/*
void EventCallback()
{
    uint8_t replyType = reply->GetOperation();
    uint8_t errorCode = reply->GetStatusCode();
    uint64_t requestId = htobe64(reply->GetID());

    std::cout << "replyType: " << (int)replyType << "\n";

    uint8_t buffer[protocol::REPLY_READ_SIZE] = {0};
    
    buffer[protocol::OPERATION_TYPE_OFFSET] = replyType;    
    memcpy(buffer + protocol::REQUEST_ID_OFFSET, &requestId, sizeof(uint64_t));
    buffer[protocol::ERROR_CODE_OFFSET] = errorCode;

    memcpy(buffer + protocol::READ_DATA_BLOCK_OFFSET, reply->DataBlock(), protocol::BLOCK_SIZE);

    m_udp.SendTo(buffer);
}
*/
} // namespace ilrd


