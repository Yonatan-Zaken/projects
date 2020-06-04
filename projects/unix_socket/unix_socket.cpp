/*********************
    Unix Socket
    CPP File
    01/06/2020
    ILRD - RD8081           
*********************/

#include <unistd.h> // close

#include "unix_socket.hpp"

namespace ilrd
{

UnixSocket::UnixSocket():
    m_sockPair()
{
      if (-1 == socketpair(AF_UNIX, SOCK_STREAM, 0, m_sockPair))
      {
          // throw
      }
}

UnixSocket::~UnixSocket() noexcept
{
    close(m_sockPair[0]);
    close(m_sockPair[1]);
}

UnixSocket::GetChildFD() const noexcept
{
    return m_sockPair[0];
}

UnixSocket::GetParentFD() const noexcept
{
    return m_sockPair[1];
}

} // namespace ilrd



