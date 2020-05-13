/*******************************
    Yonatan Zaken
    Message
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_MESSAGE_HPP
#define ILRD_RD8081_MESSAGE_HPP

#include <cinttypes> // intn_t

#include "utility.hpp"

namespace ilrd
{

class Message: private Uncopyable
{
public:	
    enum Operation
    {
        REQUEST_READ,
        REQUEST_WRITE,
        REPLY_READ,
        REPLY_WRITE
    } op_t;

    //Message(const message& other); = disabled
    //Message& operator=(const message& other); = disabled	
    virtual ~Message() = 0;
    virtual int GetID() const noexcept;
    virtual op_t GetOperation() const noexcept;
    virtual std::size_t GetBlockID() const noexcept;
    virtual std::size_t GetBlockSize() const noexcept;

private:
    uint8_t m_type;
    uint64_t m_requestID;
    static const std::size_t blockSize = 4096;
}; // class message

/******************************************************************************/

class RequestRead: public Message
{
private:
    uint64_t m_blockID;
};

/******************************************************************************/

class ReplyRead: public Message
{
private:
    char dataBlock[blockSize];
};

/******************************************************************************/

class RequestWrite: public Message
{
private:
    uint64_t m_blockID;
    char dataBlock[blockSize];
}

/******************************************************************************/

class ReplyWrite: public message
{
public:
    bool GetStatus() const noexcept;
private:
    uint8_t m_errorCode;
};

} // namespace ilrd

#endif
