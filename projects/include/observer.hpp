/*********************
    Observer
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/

#ifndef ILRD_RD8081_OBSERVER_HPP
#define ILRD_RD8081_OBSERVER_HPP

#include <boost/function.hpp> // boost::function

#include "dispatcher.hpp"
#include "utility.hpp" // Uncopyable

namespace ilrd
{

template <class PARAM>
class ObserverBase : private Uncopyable
{
public:
    explicit ObserverBase(Dispatcher<ObserverBase<PARAM>, PARAM> *dispatcher);
    virtual ~ObserverBase() noexcept {}
    //Observer(const Observer& other) = default;
    //Observer& operator=(const Observer& rhs) = default;

    virtual void Update(PARAM) = 0;
    virtual void UpdateDeath() = 0;
private:
    Dispatcher<ObserverBase<PARAM>, PARAM> *m_dispatcher;
};

/************************* ObserverBase Definitions ***************************/

template <class PARAM>
ObserverBase<PARAM>::ObserverBase(Dispatcher<ObserverBase<PARAM>, PARAM> *dispatcher):
    m_dispatcher(dispatcher)
{
}

/******************************************************************************/

template <class PARAM>
class Observer : public ObserverBase<PARAM>
{
public:
    typedef Dispatcher<ObserverBase<PARAM>, PARAM> dispatcher_t;
    typedef boost::function<void(PARAM)> updateFunc_t;
    typedef boost::function<void(void)> deathFunc_t;

    explicit Observer(dispatcher_t *dispatcher, updateFunc_t updateFunc, 
                      deathFunc_t deathFunc);
    virtual ~Observer() noexcept {}
    //Observer(const Observer& other) = default;
    //Observer& operator=(const Observer& rhs) = default;

    virtual void Update(PARAM);
    virtual void UpdateDeath();

private:
    dispatcher_t *m_dispatcher;
    updateFunc_t m_upadteFunc;
    deathFunc_t m_deathFunc;
};

} // namespace ilrd

#endif // ILRD_RD8081_OBSERVER_HPP