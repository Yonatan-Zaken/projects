/*******************************
    Yonatan Zaken
    File Name
    File Type
    //
    ILRD - RD8081               
*******************************/

#include "connection.hpp"

namespace ilrd
{

Connection::Connection(Reactor& reactor):
    m_reactor(reactor),
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

    uint8_t request_type = buffer[0];
    uint64_t *request_id = reinterpret_cast<uint64_t *>(buffer + 1);
    uint64_t *block_id = reinterpret_cast<uint64_t *>(buffer + 9);
    
    switch(request_type)
    {
        case 0:
        {
            boost::shared_ptr<Message> read_req(new RequestRead(request_type, be64toh(*request_id), be64toh(*block_id)));

            return read_req;
        }
            
        case 1:
        {
            boost::shared_ptr<Message> write_req(new RequestWrite(
            request_type, be64toh(*request_id), be64toh(*block_id), buffer + 17));

            return write_req;
        } 
    }
}

void Connection::OutputData(boost::shared_ptr<Message> reply)
{

}

} // namespace ilrd


