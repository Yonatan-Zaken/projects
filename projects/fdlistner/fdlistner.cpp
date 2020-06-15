/*******************************
    Yonatan Zaken
    FDListner
    CPP
    ILRD - RD8081               
*******************************/

#include <cerrno>       // errno
#include <cstring>      // strerror
#include <algorithm>    // for_each
#include <stdexcept>    // invalid argument

#include "fdlistner.hpp"

namespace ilrd
{

/*************************** FDExcept definitions *************************/

FDListener::ErrorExcept::ErrorExcept(int errno_val): m_errno(errno_val)
{
}

const char *FDListener::ErrorExcept::what() const noexcept
{
    return strerror(m_errno);
}

/*****************************************************************************/

struct ZeroFDFunctor
{
    void operator()(const fd_set& set)
    {
        FD_ZERO(&set);
    }
};

/*****************************************************************************/

struct SetFDFunctor
{
public:
    explicit SetFDFunctor(std::vector<fd_set>& masterFDs):
        m_masterFDs(masterFDs),
        m_fdmax(0)
    {
    }

    void operator()(const FDListener::key_t& pair)
    {
        if (FDListener::TYPE_NUM == pair.second)
        {
            throw std::invalid_argument("invalid argument");
        }
        
        FD_SET(pair.first, &m_masterFDs[pair.second]);
        m_fdmax = m_fdmax < pair.first ? pair.first : m_fdmax;
    }

    int GetMaxFD() const
    {
        return m_fdmax;
    }

private:
    std::vector<fd_set>& m_masterFDs;
    int m_fdmax;
};

/*****************************************************************************/

FDListener::vector_t FDListener::MonitorIMP(const vector_t &vector, struct timeval *timeout)
{
    std::vector<fd_set> masterFDs(FDListener::TYPE_NUM);

    std::for_each(masterFDs.begin(), masterFDs.end(), ZeroFDFunctor());
    
    int fdmax = std::for_each(vector.begin(), vector.end(), SetFDFunctor(masterFDs)).GetMaxFD();

    if (-1 == select(fdmax+1, 
                    &masterFDs[FDListener::READ], 
                    &masterFDs[FDListener::WRITE], 
                    &masterFDs[FDListener::EXCEPT], 
                    timeout)) 
    {
       throw ErrorExcept(errno);
    }

    FDListener::vector_t readyFDs;
    for(int i = 0; i <= fdmax; ++i) 
    {
        if (FD_ISSET(i, &masterFDs[FDListener::READ])) 
        { 
            readyFDs.push_back(FDListener::key_t(i, FDListener::READ));
        }

        if (FD_ISSET(i, &masterFDs[FDListener::WRITE])) 
        { 
            readyFDs.push_back(FDListener::key_t(i, FDListener::WRITE));
        }

        if (FD_ISSET(i, &masterFDs[FDListener::EXCEPT])) 
        { 
            readyFDs.push_back(FDListener::key_t(i, FDListener::EXCEPT));
        }
    }

    return readyFDs;    
}

/*****************************************************************************/

FDListener::vector_t FDListener::Monitor(const FDListener::vector_t &vector)
{
    return MonitorIMP(vector, nullptr);
}

/*****************************************************************************/

FDListener::vector_t FDListener::Monitor(const vector_t &vector, double timeOut)
{
    struct timeval timeout;
    memset(&timeout, 0, sizeof(struct timeval));

    timeout.tv_sec = static_cast<long>(timeOut);
    timeout.tv_usec = (timeOut - timeout.tv_sec) * FDListener::MILLISEC_CONVERT;
    
    return MonitorIMP(vector, &timeout);
}

/*****************************************************************************/

} // namespace ilrd
