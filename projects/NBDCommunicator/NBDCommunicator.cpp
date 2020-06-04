/*********************
    NBDCommunicator
    CPP File
    01/06/2020
    ILRD - RD8081           
*********************/

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

NBDCommunicator::~NBDCommunicator()
{
    //close device

}

/******************************************************************************/

void NBDCommunicator::Start()
{
    m_reactor.InsertFD(m_unixSocket.GetParentFD(), FDListener::READ, m_callback);

    pit_t pid = {0};
    if (0 == (pid = fork()))
    {
        close(m_unixSocket.GetChildFD());
        Ioctl();
    }

    close(m_unixSocket.GetParentFD());
    ServeNBD();
    
    if (-1 == waitpid(NULL))
    {
        LOG_ERROR("fail waitpid");
        // throw
    }
}

/**************************** Private Functions *******************************/

int NBDCommunicator::OpenDevice(const char *dev)
{
    int nbd = open(dev, O_RDWR);
    if (-1 == nbd) 
    {
        LOG_ERROR("fail to open nbd block device");
        //throw 
    }
}

/******************************************************************************/

void NBDCommunicator::InitDeviceSize(std::size_t size)
{
    if (-1 == ioctl(m_nbdFD, NBD_SET_SIZE, size))
    {
        LOG_ERROR("fail to set nbd size");
        // throw
    }

    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_SOCK))
    {
        LOG_ERROR("fail to clear nbd socket");
        // throw
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
        // throw
    }

    if (-1 == ioctl(m_nbdFD, NBD_DO_IT))
    {
        LOG_ERROR("fail to nbd do it");
        // throw
    }

    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_QUE))
    {
        LOG_ERROR("fail to nbd clear que");
        // throw
    }
    
    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_SOCK))
    {
        LOG_ERROR("fail to nbd clear sock");
        // throw
    }   
}

} // namespace ilrd

