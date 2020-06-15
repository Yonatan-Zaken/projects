/*********************
    NBDCommunicator
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_NBDCOMMUNICATOR_HPP
#define ILRD_RD8081_NBDCOMMUNICATOR_HPP

#include <boost/function.hpp>

#include "reactor.hpp"
#include "unixsocket.hpp"

namespace ilrd
{

class NBDCommunicator: private Uncopyable
{
public:	
    typedef boost::function <void(void)> callback_t;
    
    explicit NBDCommunicator(const char *dev, std::size_t numOfBlocks, Reactor& reactor);	
    // NBDCommunicator(const NBDCommunicator& other) = disabled;	
    // NBDCommunicator& operator=(const NBDCommunicator& other) = disabled;	
    ~NBDCommunicator() noexcept;

    void NBDSetUp();
    int GetMasterFD() const noexcept;
    
    class NBDCommunicatorError: public std::runtime_error
    {
    public:
        explicit NBDCommunicatorError(const char *message);
    };

private:
    UnixSocket m_unixSocket;
    Reactor &m_reactor;
    int m_nbdFD;

    int OpenDevice(const char *dev);
    void InitDeviceSize(std::size_t numOfBlocks);
    void ServeNBD();
    void Ioctl();
    void BlockSignals();
    void NBDSetSocket();
    void NBDDoIt();
    void NBDClearQueue();
    void NBDClearSocket();
};

} // namespace ilrd

#endif // ILRD_RD8081_NBDCOMMUNICATOR_HPP
