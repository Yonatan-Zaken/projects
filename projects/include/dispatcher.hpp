/*********************
    Dispatcher
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_DISPATCHER_HPP
#define ILRD_RD8081_DISPATCHER_HPP

#include <cassert> // assert
#include <vector> // std::vector
#include <utility> // std::pair
#include <algorithm> //std::for_each
#include <boost/function.hpp> // boost::function
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/weak_ptr.hpp> // boost::weak_ptr;

#include "utility.hpp" // Uncopyable

namespace ilrd
{

/*************************** Dispatcher Declaration ***************************/

template <class OBSERVER, class PARAM>
// OBSERVER must include function void Udpate(PARAM)
// OBSERVER must include function void UpdateDeath()
// PARAM must be copyable
class Dispatcher : private Uncopyable
{
public:
    // explicit Dispatcher() = default;
    virtual ~Dispatcher() noexcept;

    void Broadcast(PARAM param);

private:
    void Subscribe(OBSERVER *observer);
    void Unsubscribe(OBSERVER *observer);

    template <class U>
    friend class ObserverBase;

    enum Validity
    {
        SUBSCRIBED,
        UNSUBSCRIBED
    };

    typedef Dispatcher<OBSERVER, PARAM> dispatcher_t;
    typedef std::vector<std::pair<OBSERVER*, Validity> > observer_t;
    std::vector<std::pair<OBSERVER*, Validity> > m_observerList;

    class IsSameObserver
    {
    public:
        explicit IsSameObserver(OBSERVER *observer);
        bool operator()(const std::pair<OBSERVER*, Validity>& pair);
    private:
        OBSERVER *m_observer;
    };

    class IsUnsubscribed
    {
    public:
        bool operator()(const std::pair<OBSERVER*, Validity>& pair);
    };
};

/**************************** Dispatcher Definitions **************************/

template <class OBSERVER, class PARAM>
Dispatcher<OBSERVER, PARAM>::~Dispatcher() noexcept
{
    std::size_t size = m_observerList.size();
    for (std::size_t i = 0; i < size; ++i)
    {
        if (SUBSCRIBED == m_observerList[i].second)
        {
            m_observerList[i].first->UpdateDeath();
        }
         
    }
}

/******************************************************************************/

template <class OBSERVER, class PARAM>
void Dispatcher<OBSERVER, PARAM>::Subscribe(OBSERVER *observer)
{
    m_observerList.push_back(std::make_pair(observer, SUBSCRIBED));
}

/******************************************************************************/
/********************** IsSameObserver Functor Definitions ********************/

template <class OBSERVER, class PARAM>
Dispatcher<OBSERVER, PARAM>::IsSameObserver::IsSameObserver(OBSERVER *observer):
    m_observer(observer)
{
}

template <class OBSERVER, class PARAM>
bool Dispatcher<OBSERVER, PARAM>::IsSameObserver::operator()(const std::pair<OBSERVER*, Validity>& pair)
{
    return (pair.first == m_observer);
}

/******************************************************************************/

template <class OBSERVER, class PARAM>
void Dispatcher<OBSERVER, PARAM>::Unsubscribe(OBSERVER *observer)
{
    typename std::vector<std::pair<OBSERVER*, Validity> >::iterator it;
    it = std::find_if(m_observerList.begin(), m_observerList.end(), IsSameObserver(observer));
    
    assert(it != m_observerList.end());
    it->second = UNSUBSCRIBED;
}

/******************************************************************************/
/********************** IsUnsubscribed Functor Definitions ********************/

template <class OBSERVER, class PARAM>
bool Dispatcher<OBSERVER, PARAM>::IsUnsubscribed::operator()(const std::pair<OBSERVER*, Validity>& pair)
{
    return (UNSUBSCRIBED == pair.second);
}

/******************************************************************************/

template <class OBSERVER, class PARAM>
void Dispatcher<OBSERVER, PARAM>::Broadcast(PARAM param)
{
    std::size_t size = m_observerList.size();
    for (std::size_t i = 0; i < size; ++i)
    {
        if (SUBSCRIBED == m_observerList[i].second)
        {
            m_observerList[i].first->Update(param);
        }
    }

    m_observerList.erase(std::remove_if(m_observerList.begin(), m_observerList.end(), IsUnsubscribed()), m_observerList.end());
}

/*************************** ObserverBase Declaration *************************/

template <class PARAM>
class ObserverBase : private Uncopyable
{
public:
    explicit ObserverBase(Dispatcher<ObserverBase<PARAM>, PARAM> *dispatcher);
    virtual ~ObserverBase() noexcept;
    //Observer(const Observer& other) = default;
    //Observer& operator=(const Observer& rhs) = default;

    virtual void Update(PARAM) = 0;
    void UpdateDeath();

private:
    virtual void UpdateDeathIMP() = 0;
    Dispatcher<ObserverBase<PARAM>, PARAM> *m_dispatcher;
};

/*************************** ObserverBase Definitions *************************/

template <class PARAM>
ObserverBase<PARAM>::ObserverBase(Dispatcher<ObserverBase<PARAM>, PARAM> *dispatcher):
    m_dispatcher(dispatcher)
{
    dispatcher->Subscribe(this);
}

/******************************************************************************/

template <class PARAM>
ObserverBase<PARAM>::~ObserverBase() noexcept
{
    if (nullptr != m_dispatcher)
    {
        m_dispatcher->Unsubscribe(this);
    }
}

/******************************************************************************/

template <class PARAM>
void ObserverBase<PARAM>::UpdateDeath()
{
    m_dispatcher = nullptr;
    UpdateDeathIMP();
}

/************************** Observer Declaration ******************************/

template <class PARAM>
class Observer : public ObserverBase<PARAM>
{
public:
    typedef Dispatcher<ObserverBase<PARAM>, PARAM> dispatcher_t;
    typedef boost::function<void(PARAM)> updateFunc_t;
    typedef boost::function<void(void)> deathFunc_t;

    explicit Observer(dispatcher_t *dispatcher, updateFunc_t updateFunc, 
                      deathFunc_t deathFunc);
    virtual ~Observer() noexcept;
    //Observer(const Observer& other) = default;
    //Observer& operator=(const Observer& rhs) = default;

    virtual void Update(PARAM);
    virtual void UpdateDeathIMP();

private:
    updateFunc_t m_updateFunc;
    deathFunc_t m_deathFunc;
};

/**************************** Observer Definitions ****************************/

template <class PARAM>
Observer<PARAM>::Observer(dispatcher_t *dispatcher, updateFunc_t updateFunc, 
deathFunc_t deathFunc):
    ObserverBase<PARAM>(dispatcher),
    m_updateFunc(updateFunc),
    m_deathFunc(deathFunc)
{
}

/******************************************************************************/

template <class PARAM>
Observer<PARAM>::~Observer() noexcept
{
}

/******************************************************************************/

template <class PARAM>
void Observer<PARAM>::Update(PARAM param)
{
    m_updateFunc(param);
}

/******************************************************************************/

template <class PARAM>
void Observer<PARAM>::UpdateDeathIMP()
{
    m_deathFunc();
}

} // namespace ilrd

#endif // ILRD_RD8081_DISPATCHER_HPP


