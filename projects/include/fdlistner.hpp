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
    
    typedef std::pair<int, Operation> key_t;
    typedef std::vector<key_t> vector_t;

    static vector_t Monitor(const vector_t &vector);
    static vector_t Monitor(const vector_t &vector, double timeOut);

    class ErrorExcept: public std::exception
    {  
    public:  
        ErrorExcept(int errno_val);

        const char * what() const noexcept;

    private:
        int m_errno;
    }; 
    
private:
    static vector_t MonitorIMP(const vector_t &vector, struct timeval *timeout);
    
    static const int MILLISEC_CONVERT = 1000000;
    
}; // class FDListener

} // namespace ilrd

#endif