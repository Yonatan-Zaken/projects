/*******************************
    Yonatan Zaken
    Minion
    CPP
    ILRD - RD8081               
*******************************/

#include <boost/bind.hpp> // bind
#include <iostream>
#include "minion.hpp"

namespace ilrd
{

Minion::Minion(boost::shared_ptr<Storage> storage):
    m_storage(storage)
{
    m_reactor.InsertFD(m_connection.GetFD(), FDListener::READ,
    boost::bind(&Minion::Callback, this));
}

/*****************************************************************************/

Minion::~Minion()
{
}

/*****************************************************************************/

void Minion::Callback()
{
    boost::shared_ptr<Message> request(m_connection.GetIncomingData());
    uint8_t type = request->GetOperation();

    switch (type)
    {
    case 0:
    {
        char buffer[BLOCK_SIZE] = {0};
        uint8_t error_code = m_storage->Read(buffer, request->GetBlockID());

        boost::shared_ptr<Message> reply(new ReplyRead(request->GetOperation(), request->GetID(), error_code, buffer));

        m_connection.OutputData(reply);

        break;
    }
    
    case 1:
    {
        uint8_t error_code = m_storage->Write(request->DataBlock(), request->GetBlockID());

        boost::shared_ptr<Message> reply(new ReplyWrite(request->GetOperation(), request->GetID(), error_code));
      
        m_connection.OutputData(reply);
        break;
    }
    } // switch-case    
}

/*****************************************************************************/

void Minion::MinionStart()
{
    m_reactor.Run();
}

} // namespace ilrd


