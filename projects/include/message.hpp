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
#include "protocol_consts.hpp"

namespace ilrd
{

class Message
{
public:	
    Message(uint8_t type, uint64_t ID);
    virtual ~Message() noexcept = 0;
    //Message(const message& other); = disabled
    //Message& operator=(const message& other); = disabled	

    virtual uint64_t GetID() const noexcept;
    virtual uint8_t GetOperation() const noexcept;
    //virtual uint64_t GetBlockID() const noexcept = 0;
    //virtual uint8_t GetStatusCode() const noexcept = 0;
    //virtual uint8_t *DataBlock() const noexcept = 0;

private:
    uint8_t m_type;
    uint64_t m_requestID;
}; 

/******************************************************************************/

class RequestMessage: public Message
{
public:
    explicit RequestMessage(uint8_t type, uint64_t ID, uint64_t blockID, uint8_t *buffer);
    
    uint64_t GetBlockID() const noexcept;
    uint8_t *DataBlock() noexcept;
private:
    uint64_t m_blockId;
    uint8_t m_dataBlock[protocol::BLOCK_SIZE];
};

/******************************************************************************/

class ReplyMessage: public Message
{
public:
    explicit ReplyMessage(uint8_t type, uint64_t ID, uint8_t errorCode, const uint8_t *buffer);
    uint8_t GetStatusCode() const noexcept;
    uint8_t *DataBlock() noexcept;
private:
    uint8_t m_errorCode;
    uint8_t m_dataBlock[protocol::BLOCK_SIZE];
};

} // namespace ilrd

#endif
