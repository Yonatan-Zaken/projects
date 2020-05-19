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

/**************************** Request Read *****************************/

RequestRead::RequestRead(uint8_t type, uint64_t ID, uint64_t blockID):
    Message(type, ID),
    m_blockID(blockID)
{
}

uint64_t RequestRead::GetBlockID() const noexcept
{
    return m_blockID;
}

uint8_t *RequestRead::DataBlock() noexcept
{
    return nullptr;
}

uint8_t RequestRead::GetStatusCode() const noexcept
{
    return 0;
}

/***************************** Reply Read *******************************/

ReplyRead::ReplyRead(uint8_t type, uint64_t ID, uint8_t errorCode, uint8_t *data):
    Message(type, ID),
    m_errorCode(errorCode)
{
    memcpy(m_dataBlock, data, BLOCK_SIZE);
}

uint8_t ReplyRead::GetStatusCode() const noexcept
{
    return m_errorCode;
}

uint8_t *ReplyRead::DataBlock() noexcept
{
    return m_dataBlock;
}

uint64_t ReplyRead::GetBlockID() const noexcept
{
    return 0;
}

/***************************** Reply Write *******************************/

ReplyWrite::ReplyWrite(uint8_t type, uint64_t ID, uint8_t errorCode):
    Message(type, ID),
    m_errorCode(errorCode)
{
}

uint8_t ReplyWrite::GetStatusCode() const noexcept
{
    return m_errorCode;
}

uint64_t ReplyWrite::GetBlockID() const noexcept
{
    return 0;
}

uint8_t *ReplyWrite::DataBlock() noexcept
{
    return nullptr;
}

/***************************** Request Write *****************************/

RequestWrite::RequestWrite(uint8_t type, uint64_t ID, uint64_t blockID, const uint8_t *src):
    Message(type, ID),
    m_blockID(blockID)
{
    memcpy(m_dataBlock, src, BLOCK_SIZE);
}

uint64_t RequestWrite::GetBlockID() const noexcept
{
    return m_blockID;
}

uint8_t *RequestWrite::DataBlock() noexcept
{
    return m_dataBlock;
}

uint8_t RequestWrite::GetStatusCode() const noexcept
{
    return 0;
}


} // namespace ilrd


