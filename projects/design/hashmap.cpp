#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

template <class KEY, class VALUE, class F>
class HashMap
{
public:
    explicit HashMap(std::size_t capacity);
    VALUE& Get(const KEY& key);
    void Insert(const KEY& key, const VALUE& value);
    void Remove(const KEY& key);
private:
    std::vector<std::list<std::pair<KEY, VALUE> > > m_table;
    F m_hashFunc;
};

/************************** HashMap Implementation ****************************/

template <class KEY, class VALUE, class F>
HashMap<KEY, VALUE, F>::HashMap(std::size_t capacity):
    m_table(capacity)
{
}

/******************************************************************************/

template <class KEY, class VALUE, class F>
struct GetFunctor
{
public:
    GetFunctor(const KEY& key):
        m_key(key)
    {}

    bool operator()(const std::pair<KEY, VALUE>& node)
    {
        return (node.first == m_key);
    }
private:
    const KEY& m_key;
};

template <class KEY, class VALUE, class F>
VALUE& HashMap<KEY, VALUE, F>::Get(const KEY& key) 
{
    std::size_t index = m_hashFunc(key);
    std::list<std::pair<KEY, VALUE> >& m_entry = m_table[index];
    typename std::list<std::pair<KEY, VALUE> >::iterator it;
    
    it = std::find_if(m_entry.begin(), m_entry.end(), GetFunctor<KEY, VALUE, F>(key));

    if (it == m_entry.end())
    {
        throw std::string("key not in map");
    }
    
    return it->second;
}

/******************************************************************************/

template <class KEY, class VALUE, class F>
void HashMap<KEY, VALUE, F>::Insert(const KEY& key, const VALUE& value)
{
    std::size_t index = m_hashFunc(key);
    m_table[index].push_back(std::make_pair(key, value));
}

/******************************************************************************/

template <class KEY, class VALUE, class F>
void HashMap<KEY, VALUE, F>::Remove(const KEY& key)
{
    std::size_t index = m_hashFunc(key);
    std::list<std::pair<KEY, VALUE> >& m_entry = m_table[index];
    typename std::list<std::pair<KEY, VALUE> >::iterator it;
    
    it = std::find_if(m_entry.begin(), m_entry.end(), GetFunctor<KEY, VALUE, F>(key));

    if (it != m_entry.end())
    {
        m_entry.erase(it);
    }
}


/******************************************************************************/

struct MyKeyHash
{
    std::size_t operator()(const int& k) const
    {
        return (k % 10);
    }
};

int main()
{
    HashMap<int, std::string, MyKeyHash> hmap(10);
    hmap.Insert(3, "val1");
    hmap.Insert(4, "val2");
    hmap.Insert(5, "val3");
    
    std::cout << "value for key 5 is: " << hmap.Get(5) << "\n";
    std::cout << "value for key 4 is: " << hmap.Get(4) << "\n";
    std::cout << "value for key 3 is: " << hmap.Get(3) << "\n";

    hmap.Remove(3); 
    hmap.Remove(4);
    hmap.Remove(5);

    std::cout << "value for key 3 is: " << hmap.Get(3) << "\n";

    return 0;
}