
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

template <class T>
class Singleton: private Uncopyable
{
public:
    static T* GetInstance();

private:
    Singleton();
    static void Clean();
    static boost::atomic<T *> m_instance;
    static boost::mutex m_instantiationMutex;
    static const std::size_t DEADBEEF = 0xDEADBEEF;
};

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
            std::atexit(&Clean);
        }
    }

    return tmp;
}

template<class T>
void Singleton<T>::Clean()
{
    delete m_instance;

    std::size_t gurantee_destruction = 0xDEADBEEF;
    m_instance.store(reinterpret_cast<T*>(&gurantee_destruction), boost::memory_order_release);
}

template <class T>
boost::atomic<T *> Singleton<T>::m_instance(nullptr);

template <class T>
boost::mutex Singleton<T>::m_instantiationMutex;

} // namespace ilrd

