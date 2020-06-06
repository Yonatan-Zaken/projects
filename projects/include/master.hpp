/*********************
    Master
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_MASTER_HPP
#define ILRD_RD8081_MASTER_HPP

#include <linux/nbd.h>  // NBD_SET_SIZE

#include "utility.hpp"
#include "reactor.hpp"
#include "NBDCommunicator.hpp"

namespace ilrd
{

class Master: private Uncopyable
{
public:
    explicit Master(const char *dev, std::size_t nbdSize, std::size_t storageSize);
    ~Master() noexcept;
    // Master(const Master& other) = disabled;	
    // Master& operator=(const Master& other) = disabled;	
    
    void Callback();

private:
    Reactor m_reactor;
    char *m_storage;
    NBDCommunicator m_communicator;

    void WriteAll(int fd, char *buffer, std::size_t count);
    void ReadAll(int fd, char *buffer, std::size_t count);

};

namespace details
{

class ReadError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error reading from file descriptor";
    }
};

class WriteError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return "error writing to file descriptor";
    }
};

} // namespace details

} // namespace ilrd

#endif //ILRD_RD8081_MASTER_HPP
