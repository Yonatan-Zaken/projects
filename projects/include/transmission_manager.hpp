/*****************************
    Transmissiom manager
    HPP File
    24/06/2020
    ILRD - RD8081               
****************************/

#ifndef ILRD_RD8081_TRANSMISSION_MANAGER_HPP
#define ILRD_RD8081_TRANSMISSION_MANAGER_HPP

#include <map>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "scheduler.hpp"
#include "kamikaze.hpp"

namespace ilrd
{

class TransmissionManager
{
public:
    typedef boost::function<void(void)> func_t;
    typedef boost::chrono::nanoseconds nanoseconds_t; 

    TransmissionManager(Scheduler& scheduler, func_t retransmitFunc,
                        func_t errorFunc, nanoseconds_t interval);
    //TransmissionManager() = default;

    void Add(uint64_t key, boost::shared_ptr<char[]> packet);
    void Remove(uint64_t key);

private:
    Scheduler& m_scheduler;
    func_t m_retransmitFunc;
    func_t m_errorFunc;
    nanoseconds_t m_interval;
    std::map<uint64_t, boost::shared_ptr<char[]> > m_requestMap;

    void Action(boost::shared_ptr<char[]> packet);
    void CheckSuccess(std::pair<uint64_t, boost::shared_ptr<Kamikaze> >);
    void OnError();
};

} //namespace ilrd

#endif //ILRD_RD8081_TRANSMISSION_MANAGER_HPP
