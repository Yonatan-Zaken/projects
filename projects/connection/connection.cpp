/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/

#include <endian.h> // htobe64

#include "connection.hpp"

namespace ilrd
{

Connection::Connection():
    m_fd(m_udp.GetFD())
{
}

Connection::~Connection()
{
}

int Connection::GetFD() const noexcept
{
    return m_fd;
}

boost::shared_ptr<Message> Connection::GetIncomingData() 
{
    char buffer[BLOCK_SIZE] = {0};
    m_udp.ReceiveFrom(buffer);

    uint8_t requestType = buffer[0];
    uint64_t *requestID = reinterpret_cast<uint64_t *>(buffer + 1);
    uint64_t *blockID = reinterpret_cast<uint64_t *>(buffer + 9);
    
    switch(requestType)
    {
        case 0:
        {
            boost::shared_ptr<Message> readReq(new RequestRead(requestType, be64toh(*requestID), be64toh(*blockID)));

            return readReq;
        }
            
        case 1:
        {
            boost::shared_ptr<Message> writeReq(new RequestWrite(
            requestType, be64toh(*requestID), be64toh(*blockID), buffer + 17));

            return writeReq;
        } 
    }
}

void Connection::OutputData(boost::shared_ptr<Message> reply) 
{
    uint8_t replyType = reply->GetOperation();
    uint8_t errorCode = reply->GetStatusCode();
    uint64_t requestId = htobe64(reply->GetID());

    
    switch (replyType)
    {
    case 0:
    {
        char buffer[BLOCK_SIZE] = {0};
        buffer[0] = replyType;
        
        memcpy(reinterpret_cast<uint64_t *>(&buffer[1]), &requestId, sizeof(uint64_t));
        
        buffer[10] = errorCode;
        m_udp.SendTo(buffer);
        break;
    }
    
    case 1:
    {
        char buffer[2 * sizeof(uint8_t) + sizeof(uint64_t)] = {0};
        buffer[0] = replyType;

        memcpy(reinterpret_cast<uint64_t *>(&buffer[1]), &requestId, sizeof(uint64_t));

        buffer[10] = errorCode;
        m_udp.SendTo(buffer);
        break;
    }
    } // switch-case
}

} // namespace ilrd


