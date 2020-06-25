/*****************************
    Transmissiom manager
    CPP File
    24/06/2020
    ILRD - RD8081               
****************************/

#include "transmission_manager.hpp"

namespace ilrd
{

TransmissionManager::TransmissionManager(Scheduler& scheduler, func_t retransmitFunc, func_t errorFunc, nanoseconds_t interval):
    m_scheduler(scheduler),
    m_retransmitFunc(retransmitFunc),
    m_errorFunc(errorFunc),
    m_interval(interval),
    m_requestMap()
{
}

TransmissionManager::~TransmissionManager()
{

}

void TransmissionManager::Add(uint64_t key, boost::shared_ptr<char[]> packet)
{
    m_requestMap[key] = packet;
}

void TransmissionManager::Remove(uint64_t key)
{
    m_requestMap.erase(key);
}

/**************************** Private Definitions *****************************/

void TransmissionManager::Action(boost::shared_ptr<char[]> packet)
{
    
}
    
void TransmissionManager::CheckSuccess(std::pair<uint64_t, boost::shared_ptr<Kamikaze> > packetInfo)
{
    if (m_requestMap.end() == m_requestMap.find(packetInfo.first))
    {
        return;
    }

    else if (0 != packetInfo.second->GetCounter())
    {
        
    }
    
    else
    {
        
    }
}

void TransmissionManager::OnError()
{

}

} // namespace ilrd


