/*******************************
    Yonatan Zaken
    Shared Pointer
    HPP
    26/04/20
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_SHARED_PTR_HPP
#define ILRD_RD8081__SHARED_PTR_HPP

#include <cstddef> // std::size_t

#include "utility.hpp" // nullptr

namespace ilrd
{

template <class T>
class SharedPtr
{
public:	
    explicit SharedPtr(T *ptr = nullptr);	
    SharedPtr(const SharedPtr& other);	
    SharedPtr& operator=(const SharedPtr& rhs);	
    ~SharedPtr() noexcept;

    template <class U>
    SharedPtr(const SharedPtr<U>& other); // non-explicit conversion ctor

    T& operator*() const noexcept;
    T* operator->() const noexcept;

private:
    T *m_ptr;
    std::size_t* m_counter;

    void DecrementRC() noexcept;
    void IncrementRC() noexcept;

    template <class U>
    friend class SharedPtr;
};

/********************** SharedPtr template definitions **********************/

template <typename T>
SharedPtr<T>::SharedPtr(T *ptr):  
    m_ptr(ptr),
    m_counter(new std::size_t(1))
{
}

/****************************************************************************/

template <typename T>
SharedPtr<T>::~SharedPtr() noexcept
{
    DecrementRC();
}

/****************************************************************************/

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other): 
    m_ptr(other.m_ptr),
    m_counter(other.m_counter)
{
    IncrementRC();
}

/****************************************************************************/

template <typename T>
template <typename U>
SharedPtr<T>::SharedPtr(const SharedPtr<U>& other):
    m_ptr(other.m_ptr),
    m_counter(other.m_counter)
{
    IncrementRC();
}

/****************************************************************************/

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& rhs)
{
        
    if (this != &rhs)
    {
        DecrementRC();
        m_ptr = rhs.m_ptr;
        m_counter = rhs.m_counter;
        IncrementRC();
    }

    return *this;
}

/****************************************************************************/

template <typename T>
T& SharedPtr<T>::operator*() const noexcept
{
    return *m_ptr;
}

/****************************************************************************/

template <typename T>
T* SharedPtr<T>::operator->() const noexcept
{
    return m_ptr;
}

/****************************************************************************/

template <typename T>
void SharedPtr<T>::DecrementRC() noexcept
{
    --(*m_counter);
    if (0 == *m_counter)
    {
        delete m_ptr;
        delete m_counter;
    }
}

/****************************************************************************/

template <typename T>
void SharedPtr<T>::IncrementRC() noexcept
{
    ++(*m_counter);
}

} // namespace ilrd


#endif // SHARED_PTR
