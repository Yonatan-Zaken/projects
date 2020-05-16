/*******************************
    Yonatan Zaken
    Minion
    CPP
    ILRD - RD8081               
*******************************/
#include "minion.hpp"

namespace ilrd
{

Minion::Minion(boost::shared_ptr<Storage> storage)
{
    m_reactor.InsertFD(m_connection.GetFD(), &Minion::Callback);
}

Minion::~Minion()
{
}
 
void Minion::Callback()
{
    m_connection.CallBack();
}

} // namespace ilrd


