
/*******************************
    Yonatan Zaken
    Singleton
    HPP
    ILRD - RD8081               
*******************************/
#include <boost/atomic.hpp>         // boost::atomic
#include <boost/thread/mutex.hpp>   // boost::scoped_lock
#include <cstdlib>                  // atexit

#include "utility.hpp"              

namespace ilrd 
{

namespace details
{

class AtexitError: public std::exception
{
public:
    const char *what() const noexcept
    {
        return ("atexit error");
    }
};

} // namespace details

template <class T>
class Singleton: private Uncopyable
{
public:
    static T* GetInstance();

private:
    static boost::atomic<T *> m_instance;
    static boost::mutex m_instantiationMutex;
    
    Singleton();
    static void Clean();
    
    static std::size_t m_guranteeDestruction;
};

template <class T>
std::size_t Singleton<T>::m_guranteeDestruction = 0xDEADBEEF;

template <class T>
T* Singleton<T>::GetInstance()
{
    T *tmp = m_instance.load(boost::memory_order_consume);
    if (nullptr == tmp) 
    {
        boost::mutex::scoped_lock guard(m_instantiationMutex);
        tmp = m_instance.load(boost::memory_order_consume);
        if (nullptr == tmp)
        {
            tmp = new T;
            m_instance.store(tmp, boost::memory_order_release);
            if (-1 == std::atexit(&Clean))
            {
                delete tmp;
                throw details::AtexitError();
            }
        }
    }

    return tmp;
}

template<class T>
void Singleton<T>::Clean()
{
    delete m_instance;
    
    m_instance.store(reinterpret_cast<T*>(&m_guranteeDestruction), boost::memory_order_release);
}

template <class T>
boost::atomic<T *> Singleton<T>::m_instance(nullptr);

template <class T>
boost::mutex Singleton<T>::m_instantiationMutex;

} // namespace ilrd

