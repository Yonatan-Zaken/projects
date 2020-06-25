/*****************************
    Kamikaze
    Header File
    24/06/2020
    ILRD - RD8081               
****************************/
#ifndef ILRD_RD8081_KAMIKAZE_HPP
#define ILRD_RD8081_KAMIKAZE_HPP

#include <boost/function.hpp>
#include <boost/chrono.hpp>

namespace ilrd
{

class Kamikaze
{
public:
    typedef boost::function<void(void)> func_t;
    typedef boost::chrono::nanoseconds nanoseconds_t; 

    explicit Kamikaze(std::size_t counter, nanoseconds_t interval, func_t actionFunc, func_t checkSuccessFunc, func_t onErrorFunc);
    ~Kamikaze() noexcept {}

    std::size_t GetCounter() const;
    nanoseconds_t GetInterval() const;

private:
    std::size_t m_counter;
    nanoseconds_t m_interval;
    func_t m_action;
    func_t m_checkSuccess;
    func_t m_onError;
};

} //namespace ilrd

#endif //ILRD_RD8081_KAMIKAZE_HPP
