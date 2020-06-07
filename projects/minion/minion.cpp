/*******************************
    Yonatan Zaken
    Minion
    CPP
    ILRD - RD8081               
*******************************/

#include <boost/bind.hpp> // bind
#include <iostream>

#include "minion.hpp"
#include "protocol_consts.hpp"

namespace ilrd
{

Minion::Minion(boost::shared_ptr<Storage> storage, const char* port):
    m_storage(storage),
    m_reactor(),
    m_connection(port, m_reactor, boost::bind(&Minion::Callback, this)),
    m_factory()
{
}

/*****************************************************************************/

void Minion::Callback()
{
    boost::shared_ptr<RequestMessage> request(m_connection.ConstructRequest());
    uint8_t type = request->GetOperation();

    std::cout << type << "\n";
    std::cout << request->GetBlockID() << "\n";

    boost::shared_ptr<Command> command(m_factory.Fabricate(type, request));
    uint8_t errorCode = command->Operation(m_storage, request->DataBlock());

    boost::shared_ptr<ReplyMessage> reply(new ReplyMessage(request->GetOperation(), request->GetID(), errorCode, request->DataBlock()));

    m_connection.SendMessage(reply);
}

/*****************************************************************************/

void Minion::MinionStart()
{
    m_reactor.Run();
}

} // namespace ilrd
