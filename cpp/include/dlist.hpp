/*******************************
    Yonatan Zaken
    Dlist
    HPP
    22/04/20
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_LIST_HPP
#define ILRD_RD8081_LIST_HPP

#include <cstddef>      // size_t   
#include <string>       // string   

#include "utility.hpp"  // noexcept 

namespace ilrd
{
// template decleration
template <class T>
class DList
{
public:
    explicit DList();
    DList(const DList& other);
    DList& operator=(const DList& rhs);
    ~DList() noexcept;

    void Clear() noexcept;
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;

    void PushBack(const T& value);
    void PushFront(const T& value);
    T PopBack(); //throw exception
    T PopFront(); //throw exception
    T PeekBack(); //throw exception
    T PeekFront(); //throw exception

private:
    void DummyInitializer() noexcept;
    void CopyList(const DList&); //throw exception

private:
    struct Node
    {
    public:
        explicit Node(const T& value);
        Node(const Node& other);
        //~Node() noexcept; = default
        T m_value;
        Node *m_next;
        Node *m_prev;
    private:
        Node& operator=(const Node& rhs);
    };
    
    Node m_head;
    Node m_tail;
};

/********************** Node template definitions **********************/

template <typename T>
DList<T>::Node::Node(const T& value): 
    m_value(value), 
    m_next(NULL), 
    m_prev(NULL)
{
}

template <typename T>
DList<T>::Node::Node(const Node& other): 
    m_value(other.m_value),
    m_next(NULL), 
    m_prev(NULL) 
{
}

/********************* DList template definitions **********************/

template <typename T>
DList<T>::DList(): m_head(Node(T())), m_tail(Node(T()))
{
    DummyInitializer();
}

/***********************************************************************/

template <typename T>
DList<T>::~DList() noexcept
{
    this->Clear();
}

/***********************************************************************/

template <typename T>
DList<T>::DList(const DList& other): m_head(Node(T())), m_tail(Node(T()))
{
    DummyInitializer();
    CopyList(other);
}

/***********************************************************************/

template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs)
{   
    if (this != &rhs)
    {
        this->Clear();
        CopyList(rhs);    
    }
     
    return *this;
}

/***********************************************************************/

template <typename T>
bool DList<T>::IsEmpty() const noexcept
{
    return (m_head.m_next == &m_tail);
}

/***********************************************************************/

template <typename T>
std::size_t DList<T>::Size() const noexcept
{
    std::size_t counter = 0;
    const Node* runner = &m_head;

    for (counter = 0; &m_tail != runner->m_next; ++counter)
    {
        runner = runner->m_next;
    }

    return counter;
}

/***********************************************************************/

template <typename T>
void DList<T>::PushBack(const T& value)
{
    Node *node_holder = new Node(value);
    
    m_tail.m_prev->m_next = node_holder;
    node_holder->m_prev = m_tail.m_prev;
    
    m_tail.m_prev = node_holder;
    node_holder->m_next = &m_tail;
}

/***********************************************************************/

template <typename T>
void DList<T>::PushFront(const T& value)
{
    Node *node_holder = new Node(value);
    
    m_head.m_next->m_prev = node_holder;
    node_holder->m_next = m_head.m_next;
    
    m_head.m_next = node_holder;
    node_holder->m_prev = &m_head;
}

/***********************************************************************/

template <typename T>
T DList<T>::PopFront()
{
    if (0 == Size())
    {
        throw std::string("Error. Can't pop list is empty.");
    }
    
    Node *node_holder = m_head.m_next;
    T value_holder(m_head.m_next->m_value);

    m_head.m_next = m_head.m_next->m_next;
    m_head.m_next->m_prev = &m_head;
    delete node_holder; node_holder = NULL;

    return value_holder;
}

/***********************************************************************/

template <typename T>
T DList<T>::PopBack()
{
    if (0 == Size())
    {
        throw std::string("Error. Can't pop list is empty.");
    }
    
    Node *node_holder = m_tail.m_prev;
    T value_holder(m_tail.m_prev->m_value);

    m_tail.m_prev = m_tail.m_prev->m_prev;
    m_tail.m_prev->m_next = &m_tail;
    delete node_holder; node_holder = NULL;

    return value_holder;
}

/***********************************************************************/

template <typename T>
T DList<T>::PeekFront()
{
    if (0 == Size())
    {
        throw std::string("Error. Can't peek list is empty.");
    }
    
    return m_head.m_next->m_value;
}

/***********************************************************************/

template <typename T>
T DList<T>::PeekBack()
{
    if (0 == Size())
    {
        throw std::string("Error. Can't peek list is empty.");
    }
    
    return m_tail.m_prev->m_value;
}

/***********************************************************************/

template <typename T>
void DList<T>::Clear() noexcept
{
    while (0 == IsEmpty())
    {
         PopBack();
    }
}

/*************************** Private Functions *************************/

template <typename T>
void DList<T>::DummyInitializer() noexcept
{
    m_head.m_next = &m_tail;
    m_tail.m_prev = &m_head;
}

template <typename T>
void DList<T>::CopyList(const DList& other)
{
    const Node *runner = &other.m_head;
    while (&other.m_tail != runner->m_next)
    {
        runner = runner->m_next;
        PushBack(runner->m_value);
    }
}


} // namespace ilrd

#endif //ILRD_RD8081_LIST_HPP
