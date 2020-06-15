/*******************************
    Yonatan Zaken
    Message
    CPP
    ILRD - RD8081               
*******************************/

#include <cstring>  //memcpy

#include "message.hpp"

namespace ilrd
{

/******************************* Message *************************************/

Message::Message(uint8_t type, uint64_t ID):
    m_type(type),
    m_requestID(ID)
{
}

Message::~Message() noexcept
{
}

uint64_t Message::GetID() const noexcept
{
    return m_requestID;
}

uint8_t Message::GetOperation() const noexcept
{
    return m_type;
}

/**************************** Request Message *****************************/

RequestMessage::RequestMessage(uint8_t type, uint64_t ID, uint64_t blockID, uint8_t *data):
    Message(type, ID),
    m_blockId(blockID)
{
    memcpy(&(m_dataBlock[0]), data, protocol::BLOCK_SIZE);
}

uint64_t RequestMessage::GetBlockID() const noexcept
{
    return m_blockId;
}

uint8_t *RequestMessage::DataBlock() noexcept
{
    return &(m_dataBlock[0]);
}

/**************************** Reply Message *****************************/

ReplyMessage::ReplyMessage(uint8_t type, uint64_t ID, uint8_t errorCode, const uint8_t *data):
    Message(type, ID),
    m_errorCode(errorCode)
{
    memcpy(&(m_dataBlock[0]), data, protocol::BLOCK_SIZE);
}

uint8_t ReplyMessage::GetStatusCode() const noexcept
{
    return m_errorCode;
}

uint8_t *ReplyMessage::DataBlock() noexcept
{
    return &(m_dataBlock[0]);
}

} // namespace ilrd


