/*********************
    Minion Communicator
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_MINIONCOMMUNICATOR_HPP
#define ILRD_RD8081_MINIONCOMMUNICATOR_HPP

#include <boost/function.hpp> 

#include "reactor.hpp"
#include "UDPClient.hpp"
#include "utility.hpp"

namespace ilrd
{

class MinionCommunicator: private Uncopyable
{
public:	
    explicit MinionCommunicator(const char *port);	
    // MinionCommunicator(const MinionCommunicator& other) = disable;	
    // MinionCommunicator& operator=(const MinionCommunicator& other) = disable;
    ~MinionCommunicator() noexcept;

    void WriteRequest(u_int32_t requestType, u_int64_t blockOffset, char *requestID);
    void WriteRequest(u_int32_t requestType, u_int64_t blockOffset, char *requestID, const char *dataBlock);
    void ReadReply(char *buffer);

    inline int GetMinionFD() const noexcept;

private:
    UDPClient m_client;
    int m_minionFD;

    void BuildRequestProtocol(u_int32_t requestType, u_int64_t blockOffset, char *requestID, char *buffer);
};

inline int MinionCommunicator::GetMinionFD() const noexcept
{
    return m_minionFD;
}

} // namespace ilrd

#endif // ILRD_RD8081_MINIONCOMMUNICATOR_HPP
