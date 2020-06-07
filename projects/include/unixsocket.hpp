/*********************
    Unix Socket
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_UNIXSOCKET_HPP
#define ILRD_RD8081_UNIXSOCKET_HPP

#include <cstddef>      // std::size_t
#include <stdexcept>    // std::runtime_error

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

    inline int GetFirstFD() const noexcept;
    inline int GetSecondFD() const noexcept;

    class UnixSocketError: public std::runtime_error
    {
    public:
        explicit UnixSocketError(const char *message);
    };

private:
    static const std::size_t PAIR = 2;
    int m_sockPair[PAIR];
};

/***************************** Inline Definition ******************************/

inline int UnixSocket::GetFirstFD() const noexcept
{
    return m_sockPair[0];
}

inline int UnixSocket::GetSecondFD() const noexcept
{
    return m_sockPair[1];
}

} // namespace ilrd

#endif
