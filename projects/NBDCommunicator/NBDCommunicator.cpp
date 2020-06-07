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
    if (-1 == wait(nullptr))
    {
        LOG_ERROR("fail waitpid");
    }


    close(m_nbdFD);
}
 
/******************************************************************************/

void NBDCommunicator::Start()
{
    m_reactor.InsertFD(m_unixSocket.GetFirstFD(), FDListener::READ, m_callback);

    pid_t pid = {0};
    if (0 == (pid = fork()))
    {
        BlockSignals();
        close(m_unixSocket.GetFirstFD());
        Ioctl();
        close(m_unixSocket.GetSecondFD());
    }

    close(m_unixSocket.GetSecondFD());
    ServeNBD();
}

/******************************************************************************/

int NBDCommunicator::GetMasterFD() const noexcept
{
    return m_unixSocket.GetFirstFD();
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
    if(-1 == ioctl(m_nbdFD, NBD_SET_SOCK, m_unixSocket.GetSecondFD()))
    {
        LOG_ERROR("fail to set nbd socket");
        exit(1);
    }

    std::cout << "m_nbdFD is: " << m_nbdFD << "\n";
    if (-1 == ioctl(m_nbdFD, NBD_DO_IT))
    {
        std::cerr << "NBD_DO_IT fail\n";
        LOG_ERROR("fail to nbd do it");
        exit(1);
    }

    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_QUE))
    {
        LOG_ERROR("fail to nbd clear que");
        exit(1);
    }
    
    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_SOCK))
    {
        LOG_ERROR("fail to nbd clear sock");
        exit(1);
    }   
}

/******************************************************************************/

void NBDCommunicator::BlockSignals()
{
    sigset_t sigset;
    memset(&sigset, 0, sizeof(sigset_t));

    if ((0 != sigfillset(&sigset)) || (0 != sigprocmask(SIG_SETMASK, &sigset, nullptr)))
    {
        throw details::BlockSignalsError();
    }
}

} // namespace ilrd

