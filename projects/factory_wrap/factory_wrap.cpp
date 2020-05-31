/*******************************
    Yonatan Zaken
    Factory Wrap
    CPP
    ILRD - RD8081               
*******************************/
#include "factory_wrap.hpp"

namespace ilrd
{

FactoryWrap::FactoryWrap()
{
    m_factory.AddRecipe(0, Read::CreateRead);
    m_factory.AddRecipe(1, Write::CreateWrite);
}

/******************************************************************************/

boost::shared_ptr<Command> FactoryWrap::Fabricate(uint8_t key, Message message)
{
    return m_factory.Fabricate(key, message);
}

} // namespace ilrd


