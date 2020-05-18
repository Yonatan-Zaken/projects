
/*******************************
    Yonatan Zaken
    Singleton
    HPP
    ILRD - RD8081               
*******************************/

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>

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
    ~Singleton();
    static boost::atomic<T *> m_instance;
    static boost::mutex instantiation_mutex;
};

template <class T>
T* Singleton<T>::GetInstance()
{
    T *tmp = m_instance.load(boost::memory_order_consume);
    if (nullptr == tmp) 
    {
        boost::mutex::scoped_lock guard(instantiation_mutex);
        tmp = m_instance.load(boost::memory_order_consume);
        if (nullptr == tmp)
        {
            tmp = new T;
            m_instance.store(tmp, boost::memory_order_release);
        }
    }

    return tmp;
}

template <class T>
boost::atomic<T *> Singleton<T>::m_instance(nullptr);

} // namespace ilrd

