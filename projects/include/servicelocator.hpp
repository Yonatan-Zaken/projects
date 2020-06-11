/**************************
    Service Locator
    Hedaer File
    09/06/2020
    ILRD - RD8081           
**************************/
#ifndef ILRD_RD8081_SERVICE_LOCATOR_HPP
#define ILRD_RD8081_SERVICE_LOCATOR_HPP

#include <map>       // std::map
#include <utility>   // std::pair
#include <stdexcept> // std::invalid_argument
#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include "logger_preprocessor.hpp"
#include "utility.hpp" //noexept

namespace ilrd
{

template <class KEY>
class ServiceLocator
{
public:
    explicit ServiceLocator();
    ~ServiceLocator() noexcept {}
    
    template <class T>
    void Add(KEY key, T service);

    template <class T>
    T Get(KEY key);

    class ServiceLocatorError: public std::invalid_argument
    {   
    public:
        explicit ServiceLocatorError(const char *message);
    };

private:
    class HolderBase
    {
     public:
        //HolderBase() = default;
        //HolderBase(const HolderBase&) = default;
        //HolderBase& operator=(const HolderBase&) = default;
        virtual ~HolderBase() noexcept = 0;
    };

    template <class T>
    class Holder : public HolderBase
    {
    public:
        explicit Holder(T service);
        //Holder(const Holder&) = disabled;
        //Holder& operator=(const Holder&) = disabled;
        ~Holder() noexcept {}
        T Get() const;

    private:
        T m_service;
    };

    std::map<KEY, boost::shared_ptr<HolderBase> > m_services;
};

/************************ Service Locator Definitions *************************/

template <class KEY>
ServiceLocator<KEY>::ServiceLocator():
    m_services()
{
    LOG_INFO("Constructing ServiceLocator");
}

/******************************************************************************/

template <class KEY>
template <class T>
void ServiceLocator<KEY>::Add(KEY key, T service)
{
    LOG_INFO("Adding Service");
    m_services[key] = boost::make_shared<Holder<T> >(service);
}

/******************************************************************************/

template <class KEY>
template <class T>
T ServiceLocator<KEY>::Get(KEY key)
{
    if (m_services.end() == m_services.find(key))
    {
        throw ServiceLocatorError("invalid key entered");
    }

    Holder<T> *holder;
    holder = dynamic_cast<Holder<T> *>(m_services[key].get());
    if (nullptr == holder)
    {
        throw ServiceLocatorError("invalid service type entered");
    }

    LOG_INFO("Getting service");
    return holder->Get();
}

/**************************** Holder Definitions ******************************/

template <class KEY>
ServiceLocator<KEY>::HolderBase::~HolderBase() noexcept
{
}

/**************************** Holder Definitions ******************************/

template <class KEY>
template <class T>
ServiceLocator<KEY>::Holder<T>::Holder(T service):
    m_service(service)
{
}

/******************************************************************************/

template <class KEY>
template <class T>
T ServiceLocator<KEY>::Holder<T>::Get() const
{
    return m_service;
}

/*************************** ServiceLocatorError  *****************************/

template <class KEY>
ServiceLocator<KEY>::ServiceLocatorError::ServiceLocatorError(const char *msg):
    std::invalid_argument(msg)
{
}

} //namespace ilrd

#endif //ILRD_RD8081_SERVICE_LOCATOR_HPP