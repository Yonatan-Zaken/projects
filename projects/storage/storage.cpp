/*******************************
    Yonatan Zaken
    Storage
    CPP
    ILRD - RD8081               
*******************************/

#include <cstring>  // memcpy

#include "storage.hpp"

namespace ilrd
{

HeapStorage::HeapStorage(std::size_t numOfBlocks):
    m_storage(new char[numOfBlocks * blockSize])
{
}

/*****************************************************************************/

HeapStorage::~HeapStorage()
{
    delete[] m_storage;
    m_storage = nullptr;
}

/*****************************************************************************/

const char *HeapStorage::Read(std::size_t blockNum)
{
    return (m_storage + (blockNum * blockSize));
}

/*****************************************************************************/

void HeapStorage::Write(const char *data, std::size_t blockNum)
{
    memcpy(m_storage + (blockNum * blockSize), data, blockSize);
}

} // namespace ilrd


