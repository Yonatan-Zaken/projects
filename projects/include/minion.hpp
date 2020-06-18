/*******************************
    Yonatan Zaken
    Minion
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_MINION_HPP
#define ILRD_RD8081_MINION_HPP

#include <boost/shared_ptr.hpp>

#include "framework.hpp"

#include "reactor.hpp"
#include "storage.hpp"
#include "connection.hpp"
#include "message.hpp"
#include "factory_wrap.hpp"
#include "utility.hpp"

namespace ilrd
{

class Minion: private Uncopyable
{
public:	
    //Minion(boost::shared_ptr<Storage> storage, const char *port);
    //~Minion() noexcept = default;
    //Minion(const minion& other); = disabled	
    //Minion& operator=(const minion& other); = disabled

    Minion(ConfigurationBase *config);

    void MinionStart();
    inline int GetFD() const noexcept;

private:
    Framework m_framework;  
    boost::shared_ptr<Storage> m_storage;
    Reactor* m_reactor;
    Connection m_connection;
    FactoryWrap m_factory;

    void Callback();
};

inline int Minion::GetFD() const noexcept
{
    return m_connection.GetFD();
}

} // namespace ilrd

#endif