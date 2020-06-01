/*******************************
    Yonatan Zaken
    Factory Wrap
    CPP
    ILRD - RD8081               
*******************************/

#include "command.hpp"
#include "factory_wrap.hpp"
#include "protocol_consts.hpp"

namespace ilrd
{

FactoryWrap::FactoryWrap()
{
    m_factory.AddRecipe(protocol::READ, Read::CreateRead);
    m_factory.AddRecipe(protocol::WRITE, Write::CreateWrite);
}

/******************************************************************************/

boost::shared_ptr<Command> FactoryWrap::Fabricate(uint8_t key, boost::shared_ptr<RequestMessage> message)
{ 
    return (m_factory.Fabricate(key, *message));
}

} // namespace ilrd


