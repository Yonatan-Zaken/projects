/*******************************
    Yonatan Zaken
    Storage
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_STORAGE_HPP
#define ILRD_RD8081_STORAGE_HPP

#include <iosfwd>

#include "utility.hpp"

namespace ilrd
{

class Storage: private Uncopyable
{
public:	
    virtaul ~Storage()
    {
    }

    virtual const char *Read(std::size_t blockNum) = 0;
    virtual void Write(char *data, std::size_t blockNum) = 0;
    virtual std::size_t GetStorageSize() const noexcept = 0;
    virtual std::size_t GetFreeBlocks() const noexcept = 0;
}; // Class Storage

class HeapStorage: public Storage
{
public:
    HeapStorage(std::size_t storageSize);
    virtual ~HeapStorage();
    virtual const char *Read(std::size_t blockNum);
    virtual void Write(const char *data, std::size_t blockNum);
    virtual std::size_t GetFreeBlocks() const noexcept;

    static const std::size_t blockSize = 4096;

private:
    char *m_storage;
    std::size_t m_freeBlocks;
}

} //namespace ilrd

#endif
