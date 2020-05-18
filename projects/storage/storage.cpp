/*******************************
    Yonatan Zaken
    Storage
    CPP
    ILRD - RD8081               
*******************************/

#include <cstring>  // memcpy

#include "storage.hpp"
#include "logger.hpp"

namespace ilrd
{

HeapStorage::HeapStorage(uint64_t numOfBlocks):
    m_storage(new char[numOfBlocks * BLOCK_SIZE]),
    m_numOfBlocks(numOfBlocks)
{
}

/*****************************************************************************/

HeapStorage::~HeapStorage()
{
    delete[] m_storage;
    m_storage = nullptr;
}

/*****************************************************************************/

uint8_t HeapStorage::Read(char *buffer, uint64_t blockNum)
{
    if (blockNum > m_numOfBlocks)
    {
        return 1;
    }
    
    memcpy(buffer, m_storage + (blockNum * BLOCK_SIZE), BLOCK_SIZE);
    return 0;
}

/*****************************************************************************/

uint8_t HeapStorage::Write(const char *data, uint64_t blockNum)
{
    if (blockNum > m_numOfBlocks)
    {
        return 1;
    }

    memcpy(m_storage + (blockNum * BLOCK_SIZE), data, BLOCK_SIZE);
    return 0;
}

} // namespace ilrd


