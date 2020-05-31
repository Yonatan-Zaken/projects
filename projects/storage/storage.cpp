/*******************************
    Yonatan Zaken
    Storage
    CPP
    ILRD - RD8081               
*******************************/

#include <cstring>  // memcpy

#include "storage.hpp"
#include "protocol_consts.hpp"

namespace ilrd
{

HeapStorage::HeapStorage(uint64_t numOfBlocks):
    m_storage(new uint8_t[numOfBlocks * protocol::BLOCK_SIZE]),
    m_numOfBlocks(numOfBlocks)
{
}

/*****************************************************************************/

HeapStorage::~HeapStorage() noexcept
{
    delete[] m_storage;
    m_storage = nullptr;
}

/*****************************************************************************/

uint8_t HeapStorage::Read(uint8_t *buffer, uint64_t blockNum)
{
    if (blockNum >= m_numOfBlocks)
    {
        return 1;
    }
    
    memcpy(buffer, m_storage + (blockNum * protocol::BLOCK_SIZE), protocol::BLOCK_SIZE);
    return 0;
}

/*****************************************************************************/

uint8_t HeapStorage::Write(const uint8_t *data, uint64_t blockNum)
{
    if (blockNum >= m_numOfBlocks)
    {
        return 1;
    }

    memcpy(m_storage + (blockNum * protocol::BLOCK_SIZE), data, protocol::BLOCK_SIZE);
    return 0;
}

} // namespace ilrd


