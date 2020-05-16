/*******************************
    Yonatan Zaken
    Reactor
    CPP
    ILRD - RD8081               
*******************************/
#include <cassert>   // assert
#include <iostream>
#include "reactor.hpp"

namespace ilrd
{

/*****************************************************************************/

struct GetFirstFunctor
{
    FDListener::key_t operator()(std::pair<FDListener::key_t,          Reactor::callback_t> pair)
    {
        return pair.first;
    }
};

/*****************************************************************************/

struct CallbackFunctor
{
public:
    CallbackFunctor(Reactor::map_t& map):
        m_map(map)
    {
    }

    void operator()(const FDListener::key_t pair)
    {
        (m_map[pair])();
    }

private:
    Reactor::map_t& m_map;
};

/*****************************************************************************/

struct StopFunctor
{
public:
    StopFunctor(Reactor::map_t& map):
        m_map(map)
    {
    }

    bool operator()(const FDListener::key_t pair) const
    {
        return (&Reactor::Stop == m_map[pair]);
    }

private:
    Reactor::map_t& m_map;
};

/*****************************************************************************/

void Reactor::Run()
{
    m_stopFlag = 0;
    FDListener::vector_t pairsToListen;

    while (!m_stopFlag)
    {
        std::transform(m_handlerMap.begin(), m_handlerMap.end(), 
                    std::back_inserter(pairsToListen), GetFirstFunctor());
        
        FDListener::vector_t readyFDs = m_monitor.Monitor(pairsToListen);
        
        for (FDListener::vector_t::iterator it = readyFDs.begin(); 
            (it != readyFDs.end()) && (!m_stopFlag); ++it)
        {
            if (m_handlerMap.end() != m_handlerMap.find(*it))
            {
                m_handlerMap[*it]();
            }
        }
    }
}

/*****************************************************************************/

void Reactor::Stop()
{
    m_stopFlag = 1;
}

/*****************************************************************************/

void Reactor::InsertFD(int fd, FDListener::Operation service, callback_t callback)
{
    FDListener::key_t newPair(fd, service);
    
    assert(m_handlerMap.end() == m_handlerMap.find(newPair));

    m_handlerMap.insert(std::pair<FDListener::key_t, callback_t>(newPair, callback));
}

/*****************************************************************************/

void Reactor::RemoveFD(int fd, FDListener::Operation service)
{
    FDListener::key_t removePair(fd, service);

    assert(m_handlerMap.end() != m_handlerMap.find(removePair));

    m_handlerMap.erase(removePair);
}

} // namespace ilrd


