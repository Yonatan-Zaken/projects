/*********************
    Minion Communicator
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_MINIONCOMMUNICATOR_HPP
#define ILRD_RD8081_MINIONCOMMUNICATOR_HPP

#include "utility.hpp"

namespace ilrd
{

class MinionCommunicator: private Uncopyable
{
public:	
    explicit MinionCommunicator();	
    // MinionCommunicator(const MinionCommunicator& other) = disable;	
    // MinionCommunicator& operator=(const MinionCommunicator& other) = disable;
    ~MinionCommunicator() noexcept;
private:
    int m_minionFD;
};

} // namespace ilrd

#endif // ILRD_RD8081_MINIONCOMMUNICATOR_HPP
