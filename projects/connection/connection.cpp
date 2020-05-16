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

void Connection::Receive()
{
    
}

void Connection::GetIncomingData()
{
    char buffer[BLOCK_SIZE] = {0};
    m_udp.ReceiveFrom(buffer);

    uint8_t request_type = buffer[0];
    uint64_t *request_id = static_cast<uint64_t *>(buffer + 1);
    uint64_t *block_id = static_cast<uint65_t *>(buffer + 9);
    

    switch(request_type)
    {
        case 0:
            RequestRead read_req(request_type, *request_id, *block_id);
        case 1:
            RequestWrite write_req(request_type, *request_id, *block_id, buffer + 17);
    }

}



} // namespace ilrd


