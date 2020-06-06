/*********************
    Unix Socket
    CPP File
    01/06/2020
    ILRD - RD8081           
*********************/

#include <unistd.h> // close

#include "logger_preprocessor.hpp"
#include "unixsocket.hpp"

namespace ilrd
{

UnixSocket::UnixSocket():
    m_sockPair()
{
      if (-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, m_sockPair))
      {
          LOG_ERROR("socketpair failed");
          throw details::SockPairError();
      }
}

/******************************************************************************/

UnixSocket::~UnixSocket() noexcept
{
    if (-1 == close(m_sockPair[0]))
    {
        LOG_ERROR("close syscall failed");
    }
    
    if (-1 == close (m_sockPair[1]))
    {
        LOG_ERROR("close syscall failed");
    }
}

/******************************************************************************/

int UnixSocket::GetChildFD() const noexcept
{
    return m_sockPair[0];
}

/******************************************************************************/

int UnixSocket::GetParentFD() const noexcept
{
    return m_sockPair[1];
}

} // namespace ilrd



