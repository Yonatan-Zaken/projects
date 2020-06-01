/*******************************
    Yonatan Zaken
    Factory Wrap
    HPP
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_FACTORY_WRAP_HPP
#define ILRD_RD8081_FACTORY_WRAP_HPP

#include <inttypes.h>

#include "message.hpp"
#include "command.hpp"
#include "utility.hpp"
#include "factory.hpp"

namespace ilrd
{

class FactoryWrap: private Uncopyable
{
public:
    explicit FactoryWrap();
    //~FactoryWrap() = default;
    //FactoryWrap(const FactoryWrap&) = default;
    //FactoryWrap& operator=(const FactoryWrap&) = default;

    boost::shared_ptr<Command> Fabricate(uint8_t key, boost::shared_ptr<RequestMessage> message);
private:
    Factory<Command, uint8_t, RequestMessage> m_factory;
};

} // namespace ilrd

#endif