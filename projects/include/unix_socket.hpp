/*********************
    Unix Socket
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_UNIXSOCKET_HPP
#define ILRD_RD8081_UNIXSOCKET_HPP

#include <sys/socket.h>
#include <cstddef>

#include "utility.hpp"

namespace ilrd
{

class UnixSocket: private Uncopyable
{
public:	
    explicit UnixSocket();	
    ~UnixSocket() noexcept;
    // UnixSocket(const UnixSocket& other) = disabled;	
    // UnixSocket& operator=(const UnixSocket& other) = disabled;	

    int GetChildFD() const noexcept;
    int GetParentFD() const noexcept;

private:
    static const std::size_t PAIR = 2;
    int m_sockPair[PAIR];
};

} // namespace ilrd

#endif
