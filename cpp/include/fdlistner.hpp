/*******************************
    Yonatan Zaken
    FDListner
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_FD_LISTNER_HPP
#define ILRD_RD8081_FD_LISTNER_HPP

#include <vector>
#include <utility>      // std::pair
#include <sys/select.h> // fd_set

#include "utility.hpp"

namespace ilrd
{

class FDListener
{
public:
    //FDListner() = default
    //~FDListner() = default
    //FDListner(const FDListner&) = default
    //FDListner& operator=(const FDListner&) = default

    enum Operation
    {
        READ,
        WRITE,
        EXCEPT,
        TYPE_NUM
    };
    
    typedef std::pair<int, Operation> pair_t;
    typedef std::vector<pair_t> vector_t;

    static std::vector<pair_t> Monitor(const std::vector<pair_t> &vector);
    static std::vector<pair_t> Monitor(const std::vector<pair_t> &vector, double timeOut);

private:
    void InitSets();
    
};

} // namespace ilrd

#endif