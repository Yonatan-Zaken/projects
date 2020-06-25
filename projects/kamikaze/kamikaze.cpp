/*****************************
    Kamikaze
    CPP File
    24/06/2020
    ILRD - RD8081               
****************************/
#include "kamikaze.hpp"

namespace ilrd
{

Kamikaze::Kamikaze(std::size_t counter, nanoseconds_t interval, func_t actionFunc, func_t checkSuccessFunc, func_t onErrorFunc):
    m_counter(counter),
    m_interval(interval),
    m_action(actionFunc),
    m_checkSuccess(checkSuccessFunc),
    m_onError(onErrorFunc)
{
}

Kamikaze::~Kamikaze() noexcept 
{
}

std::size_t Kamikaze::GetCounter() const
{
    return m_counter;
}

nanoseconds_t Kamikaze::GetInterval() const
{
    return m_interval;
}

} // namespace ilrd
