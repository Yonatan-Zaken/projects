/*******************************
    Yonatan Zaken
    Data Block
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_DATA_BLOCK_HPP
#define ILRD_RD8081_DATA_BLOCK_HPP

#include <iosfwd> // std::size_t
#include <boost/shared_ptr.hpp>

namespace ilrd
{

template<class T, std::size_t size>
class DataBlock
{
public:	
    DataBlock();	
    DataBlock(const DataBlock& other);	
    DataBlock& operator=(const DataBlock& other);	
    ~DataBlock();

    

private:
    boost::shared_ptr<T[size]> m_dataBlock;

};

template<class T, std::size_t size>
DataBlock<T, size>::DataBlock():
    m_dataBlock(new T[size])
{
}

template<class T, std::size_t size>
DataBlock<T, size>::~DataBlock()
{
}

template<class T, std::size_t size>
DataBlock<T, size>::DataBlock(const DataBlock& other)
{

}

template<class T, std::size_t size>
DataBlock<T, size>& DataBlock<T, size>::operator=(const DataBlock& rhs)
{

}

} // namespace ilrd

#endif
