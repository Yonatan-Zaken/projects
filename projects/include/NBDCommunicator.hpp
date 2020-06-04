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
#include "unix_socket.hpp"

namespace ilrd
{

class NBDCommunicator: private Uncopyable
{
public:	
    typedef boost::function <void(void)> callback_t;

    explicit NBDCommunicator(const char *dev, std::size_t size, Reactor& reactor, callback_t callback);	
    // NBDCommunicator(const NBDCommunicator& other) = disabled;	
    // NBDCommunicator& operator=(const NBDCommunicator& other) = disabled;	
    ~NBDCommunicator() noexcept;

    int GetMasterFD();
    int GetNBDFD();

    void Start();
    
private:
    UnixSocket m_unixSocket;
    callback_t m_callback;
    Reactor &m_reactor;
    int m_nbdFD;

    int OpenDevice(const char *dev);
    void InitDeviceSize(std::size_t size);
    void ServeNBD();
    void Ioctl();
};

} // namespace ilrd

#endif // ILRD_RD8081_NBDCOMMUNICATOR_HPP
