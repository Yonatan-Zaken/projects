/*******************************
    Yonatan Zaken
    Message
    CPP
    ILRD - RD8081               
*******************************/

#include "message.hpp"

namespace ilrd
{

/******************************* Message *************************************/

Message::Message(uint8_t type, uint64_t ID):
    m_type(type),
    m_requestID(ID)
{
}

Message::~Message()
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

/***************************** Reply Read *******************************/

ReplyRead::ReplyRead(uint8_t type, uint64_t ID):
    Message(type, ID)
{
}

/***************************** Reply Write *******************************/

ReplyWrite::ReplyWrite(uint8_t type, uint64_t ID, uint8_t errorCode):
    Message(type, ID),
    m_errorCode(errorCode)
{
}

bool ReplyWrite::GetStatus() const noexcept
{
    return m_errorCode;
}

/***************************** Request Write *****************************/

RequestWrite::RequestWrite(uint8_t type, uint64_t ID, uint64_t blockID):
    Message(type, ID),
    m_blockID(blockID)
{
}

uint64_t RequestWrite::GetBlockID() const noexcept
{
    return m_blockID;
}

} // namespace ilrd


