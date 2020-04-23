/*******************************
    Yonatan Zaken
    Scope Guard
    HPP
    23/04/2020
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_SCOPE_GUARD_HPP
#define ILRD_RD8081_SCOPE_GUARD_HPP

#include "utility.hpp"

namespace ilrd
{

template <class T, void(T::*acquire)(), void(T::*release)()>
class ScopeGuard: private Uncopyable
{
public:
    ScopeGuard(T& resource);
    ~ScopeGuard() noexcept;

private:
    T& m_resource;
};

/********************** Scopeguard template definitions **********************/

template <class T, void(T::*acquire)(), void(T::*release)()>
ScopeGuard<T, acquire, release>::ScopeGuard(T& resource): 
    m_resource(resource)
{
    (m_resource.*acquire)();
}

template <class T, void(T::*acquire)(), void(T::*release)()>
ScopeGuard<T, acquire, release>::~ScopeGuard() noexcept
{
    (m_resource.*release)();
}

#endif // ILRD_RD8081_SCOPE_GUARD_HPP

}