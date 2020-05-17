/*******************************
    Yonatan Zaken
    Message
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_MESSAGE_HPP
#define ILRD_RD8081_MESSAGE_HPP

#include <inttypes.h> // intn_t

#include "utility.hpp"

namespace ilrd
{

class Message: private Uncopyable
{
public:	
    Message(uint8_t type, uint64_t ID);
    virtual ~Message() = 0;
    //Message(const message& other); = disabled
    //Message& operator=(const message& other); = disabled	

    virtual uint64_t GetID() const noexcept;
    virtual uint8_t GetOperation() const noexcept;
    virtual uint64_t GetBlockID() const noexcept = 0;
    virtual char *DataBlock() noexcept = 0;
    static const uint64_t BLOCK_SIZE = 4113;

private:
    uint8_t m_type;
    uint64_t m_requestID;
}; // class message

/******************************************************************************/

class RequestRead: public Message
{
public:
    RequestRead(uint8_t type, uint64_t ID, uint64_t blockID);
    uint64_t GetBlockID() const noexcept;
private:
    uint64_t m_blockID;
    char *DataBlock() noexcept
    {
        return nullptr;
    }
};

/******************************************************************************/

class ReplyRead: public Message
{
public:
    ReplyRead(uint8_t type, uint64_t ID, uint8_t errorCode, char *data);
private:
    uint8_t m_errorCode;
    char m_dataBlock[BLOCK_SIZE];
    uint64_t GetBlockID() const noexcept
    {
        return 0;
    }
    
    char *DataBlock() noexcept
    {
        return nullptr;
    }
};

/******************************************************************************/

class RequestWrite: public Message
{
public:
    RequestWrite(uint8_t type, uint64_t ID, uint64_t blockID, const char *src);
    uint64_t GetBlockID() const noexcept;
    char *DataBlock() noexcept;
    
private:
    uint64_t m_blockID;
    char m_dataBlock[BLOCK_SIZE];
};

/******************************************************************************/

class ReplyWrite: public Message
{

public:
    ReplyWrite(uint8_t type, uint64_t ID, uint8_t errorCode);
    uint8_t GetStatus() const noexcept;
private:
    uint8_t m_errorCode;
    uint64_t GetBlockID() const noexcept
    {
        return 0;
    }

    char *DataBlock() noexcept
    {
        return nullptr;
    }
};

} // namespace ilrd

#endif
