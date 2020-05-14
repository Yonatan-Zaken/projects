/*******************************
    Yonatan Zaken
    Storage
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_STORAGE_HPP
#define ILRD_RD8081_STORAGE_HPP

#include <iosfwd>   // std::size_t

#include "utility.hpp"

namespace ilrd
{

class Storage: private Uncopyable
{
public:	
    virtual ~Storage()
    {
    }

    virtual const char *Read(std::size_t blockNum) = 0;
    virtual void Write(const char *data, std::size_t blockNum) = 0;
}; // class Storage

class HeapStorage: public Storage
{
public:
    HeapStorage(std::size_t numOfBlocks);
    virtual ~HeapStorage();
    virtual const char *Read(std::size_t blockNum);
    virtual void Write(const char *data, std::size_t blockNum);

    static const std::size_t blockSize = 4096;

private:
    char *m_storage;
}; // class HeapStorage

} //namespace ilrd

#endif
