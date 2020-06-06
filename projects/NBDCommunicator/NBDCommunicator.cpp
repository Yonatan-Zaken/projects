/*********************
    NBDCommunicator
    CPP File
    01/06/2020
    ILRD - RD8081           
*********************/

#include <sys/wait.h>   // waitpid
#include <sys/types.h>  // pid_t
#include <fcntl.h>  // O_RDWR
#include <linux/nbd.h>  // NBD_SET_SIZE
#include <sys/ioctl.h>  // ioctl

#include "NBDCommunicator.hpp"
#include "logger_preprocessor.hpp"

namespace ilrd
{

NBDCommunicator::NBDCommunicator(const char *dev, std::size_t sizeOfDev, Reactor& reactor, callback_t callback):
    m_unixSocket(),
    m_callback(callback),
    m_reactor(reactor),
    m_nbdFD(OpenDevice(dev))
{
    InitDeviceSize(sizeOfDev);
}

/******************************************************************************/

NBDCommunicator::~NBDCommunicator() noexcept
{
    //close device
}
 
/******************************************************************************/

void NBDCommunicator::Start()
{
    m_reactor.InsertFD(m_unixSocket.GetParentFD(), FDListener::READ, m_callback);

    pid_t pid = {0};
    if (0 == (pid = fork()))
    {
        close(m_unixSocket.GetChildFD());
        Ioctl();
    }

    close(m_unixSocket.GetParentFD());
    ServeNBD();
    
    if (-1 == wait(nullptr))
    {
        LOG_ERROR("fail waitpid");
        throw details::WaitError();
    }
}

/******************************************************************************/

int NBDCommunicator::GetMasterFD() const noexcept
{
    return m_unixSocket.GetChildFD();
}

/**************************** Private Functions *******************************/

int NBDCommunicator::OpenDevice(const char *dev)
{
    int nbdFD = open(dev, O_RDWR);
    if (-1 == nbdFD) 
    {
        LOG_ERROR("fail to open nbd block device");
        throw details::OpenDeviceError(); 
    }

    return nbdFD;
}

/******************************************************************************/

void NBDCommunicator::InitDeviceSize(std::size_t size)
{
    if (-1 == ioctl(m_nbdFD, NBD_SET_SIZE, size))
    {
        LOG_ERROR("fail to set nbd size");
        throw details::NBDSetSizeError();
    }

    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_SOCK))
    {
        LOG_ERROR("fail to clear nbd socket");
        throw details::NBDClearSocketError();
    }
}

/******************************************************************************/

void NBDCommunicator::ServeNBD()
{
    m_reactor.Run();
}

/******************************************************************************/

void NBDCommunicator::Ioctl()
{
    if(-1 == ioctl(m_nbdFD, NBD_SET_SOCK, m_unixSocket.GetParentFD()))
    {
        LOG_ERROR("fail to set nbd socket");
        throw details::NBDSetSocketError();
    }

    if (-1 == ioctl(m_nbdFD, NBD_DO_IT))
    {
        LOG_ERROR("fail to nbd do it");
        throw details::NBDDoItError();
    }

    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_QUE))
    {
        LOG_ERROR("fail to nbd clear que");
        throw details::NBDClearQueueError();
    }
    
    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_SOCK))
    {
        LOG_ERROR("fail to nbd clear sock");
        throw details::NBDClearSocketError();
    }   
}

/******************************************************************************/

} // namespace ilrd

