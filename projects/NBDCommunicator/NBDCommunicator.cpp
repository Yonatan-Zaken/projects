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

#include "protocol_consts.hpp"
#include "NBDCommunicator.hpp"
#include "logger_preprocessor.hpp"

namespace ilrd
{

/************************* Exception Definition *******************************/

NBDCommunicator::NBDCommunicatorError::NBDCommunicatorError(const char *msg):
    std::runtime_error(msg)
{
}

/*********************** NBD Communicator Definitions *************************/

NBDCommunicator::NBDCommunicator(const char *dev, std::size_t numOfBlocks, Reactor& reactor):
    m_unixSocket(),
    m_reactor(reactor),
    m_nbdFD(OpenDevice(dev))
{
    InitDeviceSize(numOfBlocks);
}

/******************************************************************************/

NBDCommunicator::~NBDCommunicator() noexcept
{
    if (-1 == wait(nullptr))
    {
        LOG_ERROR("fail waitpid");
    }

    if(-1 == ioctl(m_nbdFD, NBD_DISCONNECT)) 
    {
        LOG_ERROR("fail to disconnect nbd");
    }

    close(m_nbdFD);
}
 
/******************************************************************************/

void NBDCommunicator::NBDSetUp()
{
    pid_t pid = {0};

    if (-1 == (pid = fork()))
    {
        throw NBDCommunicator::NBDCommunicatorError("fail to fork process");
    }
    
    else if (0 == pid)
    {
        BlockSignals();
        close(m_unixSocket.GetFirstFD());
        Ioctl();
        close(m_unixSocket.GetSecondFD());
    }

    close(m_unixSocket.GetSecondFD());
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
        throw NBDCommunicator::NBDCommunicatorError("error opening network block device");
    }

    return nbdFD;
}

/******************************************************************************/

void NBDCommunicator::InitDeviceSize(std::size_t numOfBlocks)
{
    if (-1 == ioctl(m_nbdFD, NBD_SET_BLKSIZE, protocol::BLOCK_SIZE))
    {
        LOG_ERROR("fail to set nbd block size");
        throw NBDCommunicator::NBDCommunicatorError("error setting nbd block size");
    }
    
    if (-1 == ioctl(m_nbdFD, NBD_SET_SIZE_BLOCKS, numOfBlocks))
    {
        LOG_ERROR("fail to set nbd num of blocks");
        throw NBDCommunicator::NBDCommunicatorError("error setting nbd num of blocks");
    }

    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_SOCK))
    {
        LOG_ERROR("fail to clear nbd socket");
        throw NBDCommunicator::NBDCommunicatorError("error clearing nbd socket");
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
    NBDSetSocket();
    NBDDoIt();
    NBDClearQueue();
    NBDClearSocket();
}

/******************************************************************************/

void NBDCommunicator::BlockSignals()
{
    sigset_t sigset = {0};

    if ((0 != sigfillset(&sigset)) || (0 != sigprocmask(SIG_SETMASK, &sigset, nullptr)))
    {
        throw NBDCommunicator::NBDCommunicatorError("error blocking signals");
    }
}

/******************************************************************************/

void NBDCommunicator::NBDSetSocket()
{
    if(-1 == ioctl(m_nbdFD, NBD_SET_SOCK, m_unixSocket.GetSecondFD()))
    {
        LOG_ERROR("fail to set nbd socket");
        exit(1);
    }
}

/******************************************************************************/

void NBDCommunicator::NBDDoIt()
{
    if (-1 == ioctl(m_nbdFD, NBD_DO_IT))
    {
        LOG_ERROR("fail to nbd do it");
        exit(1);
    }
}

/******************************************************************************/

void NBDCommunicator::NBDClearQueue()
{
    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_QUE))
    {
        LOG_ERROR("fail to nbd clear que");
        exit(1);
    }
}

/******************************************************************************/
    
void NBDCommunicator::NBDClearSocket()
{
    if (-1 == ioctl(m_nbdFD, NBD_CLEAR_SOCK))
    {
        LOG_ERROR("fail to nbd clear sock");
        exit(1);
    }    
}

} // namespace ilrd

