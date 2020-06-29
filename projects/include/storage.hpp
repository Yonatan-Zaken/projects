/*******************************
    Yonatan Zaken
    Storage
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_STORAGE_HPP
#define ILRD_RD8081_STORAGE_HPP

#include <iosfwd>       // std::size_t
#include <inttypes.h>   //uintn_t

#include "utility.hpp"

namespace ilrd
{

class Storage: private Uncopyable
{
public:
    virtual ~Storage() noexcept
    {
    }

    virtual uint8_t Read(uint8_t *buffer, uint64_t blockNum) = 0;
    virtual uint8_t Write(const uint8_t *data, uint64_t blockNum) = 0;
}; 

/******************************************************************************/

class HeapStorage: public Storage
{
public:
    HeapStorage(std::string storagePath);
    virtual ~HeapStorage() noexcept;
    virtual uint8_t Read(uint8_t *buffer, uint64_t blockNum);
    virtual uint8_t Write(const uint8_t *data, uint64_t blockNum);
    
private:
    //uint8_t *m_storage;
    //uint64_t m_numOfBlocks;
    std::string m_storagePath;
}; 

} //namespace ilrd

#endif
