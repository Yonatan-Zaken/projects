/*******************************
    Yonatan Zaken
    Minion
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_MINION_HPP
#define ILRD_RD8081_MINION_HPP

#include <boost/shared_ptr.hpp>

#include "utility.hpp"
#include "reactor.hpp"
#include "storage.hpp"
#include "connection.hpp"
#include "message.hpp"

namespace ilrd
{

class Minion: private Uncopyable
{
public:	
    Minion(boost::shared_ptr<Storage> storage);	
    ~Minion();
    //Minion(const minion& other); = disabled	
    //Minion& operator=(const minion& other); = disabled	

    void Callback();

private:
    Reactor m_reactor;
    Connection m_connection;
    boost::shared_ptr<Storage> m_storage;
    boost::shared_ptr<Message> m_message;
};

} // namespace ilrd

#endif

