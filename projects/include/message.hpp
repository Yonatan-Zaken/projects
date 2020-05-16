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
    static const uint64_t blockSize = 4113;

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
};

/******************************************************************************/

class ReplyRead: public Message
{
public:
    ReplyRead(uint8_t type, uint64_t ID, char *data);
private:
    char m_dataBlock[blockSize];
};

/******************************************************************************/

class RequestWrite: public Message
{
public:
    RequestWrite(uint8_t type, uint64_t ID, uint64_t blockID, const char *src);
    uint64_t GetBlockID() const noexcept;

private:
    uint64_t m_blockID;
    char m_dataBlock[blockSize];
};

/******************************************************************************/

class ReplyWrite: public Message
{

public:
    ReplyWrite(uint8_t type, uint64_t ID, uint8_t errorCode);
    bool GetStatus() const noexcept;
private:
    uint8_t m_errorCode;
};

} // namespace ilrd

#endif
