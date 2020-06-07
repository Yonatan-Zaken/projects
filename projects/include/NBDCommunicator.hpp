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
    
    explicit NBDCommunicator(const char *dev, std::size_t size, Reactor& reactor, callback_t callback);	
    // NBDCommunicator(const NBDCommunicator& other) = disabled;	
    // NBDCommunicator& operator=(const NBDCommunicator& other) = disabled;	
    ~NBDCommunicator() noexcept;

    void Start();
    int GetMasterFD() const noexcept;
    
private:
    UnixSocket m_unixSocket;
    callback_t m_callback;
    Reactor &m_reactor;
    int m_nbdFD;

    int OpenDevice(const char *dev);
    void InitDeviceSize(std::size_t size);
    void ServeNBD();
    void Ioctl();
    void BlockSignals();
};

/**************************** Exception Details *******************************/

namespace details
{

class WaitError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error calling wait";
    }
};

class OpenDeviceError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error opening network block device";
    }
};

class NBDSetSizeError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error setting nbd size";
    }
};

class NBDClearSocketError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error clearing nbd socket";
    }
};

class NBDSetSocketError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error setting nbd socket";
    }
};

class NBDDoItError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error nbd do it";
    }
};

class NBDClearQueueError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error clearing nbd queue";
    }
};

class BlockSignalsError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error blocking signals";
    }
};

} // namespace details


} // namespace ilrd

#endif // ILRD_RD8081_NBDCOMMUNICATOR_HPP
