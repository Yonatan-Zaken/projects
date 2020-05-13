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

namespace ilrd
{

class Minion: private Uncopyable
{
public:	
    Minion(boost::shared_ptr<Storage> storage, std::size storageSize);	
    ~Minion();
    //Minion(const minion& other); = disabled	
    //Minion& operator=(const minion& other); = disabled	
    
    void Callback();

    std::size_t FreeBlocks();
    std::size_t GetBlockSize();

private:
    Reactor m_reactor;
    Connection m_connection;
    boost::shared_ptr<Storage> m_storage;
};

} // namespace ilrd

#endif

