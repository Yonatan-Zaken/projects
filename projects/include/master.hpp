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
    explicit Master(const char *dev, std::size_t size);
    ~Master() noexcept;
    // Master(const Master& other) = disabled;	
    // Master& operator=(const Master& other) = disabled;	
    
    void Callback();

private:
    NBDCommunicator m_communicator;
    Reactor m_reactor;
};

} // namespace ilrd

#endif //ILRD_RD8081_MASTER_HPP
