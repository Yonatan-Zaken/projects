/*******************************
    Yonatan Zaken
    Storage
    CPP
    ILRD - RD8081               
*******************************/

#include <cstring>  // memcpy
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "storage.hpp"
#include "protocol_consts.hpp"

namespace ilrd
{

HeapStorage::HeapStorage(std::string storagePath):
    //m_storage(new uint8_t[numOfBlocks * protocol::BLOCK_SIZE]),
    //m_numOfBlocks(numOfBlocks)
    m_storagePath(storagePath)
{
}

/*****************************************************************************/

HeapStorage::~HeapStorage() noexcept
{
    //delete[] m_storage;
    //m_storage = nullptr;
}

/*****************************************************************************/

uint8_t HeapStorage::Read(uint8_t *buffer, uint64_t blockNum)
{
    /*
    if (blockNum >= m_numOfBlocks)
    {
        return 1;
    }
    */

    char block[50];
    sprintf(block, "%ld", blockNum);
    std::string blockIndex(block);

    std::cout << "storage read path: " << (m_storagePath + blockIndex).c_str() << "\n";

    int fd = 0;
    if (-1 == (fd = open((m_storagePath + blockIndex).c_str(), O_RDONLY, S_IRUSR)))
    {
        std::cout << "fail open storage\n";
        return 1;
    }
    
    int read_bytes;
    if (-1 == (read_bytes = read(fd, buffer, protocol::BLOCK_SIZE)))
    {
        return 1;
    }
    
    std::cout << "read bytes in storage: " << read_bytes << "\n";

    if (-1 == close(fd))
    {
        return 1;
    }
    
    //memcpy(buffer, m_storage + (blockNum * protocol::BLOCK_SIZE), protocol::BLOCK_SIZE);
    
    return 0;
}

/*****************************************************************************/

uint8_t HeapStorage::Write(const uint8_t *data, uint64_t blockNum)
{
    /*
    if (blockNum >= m_numOfBlocks)
    {
        return 1;
    }
    */
    char block[50];
    sprintf(block, "%ld", blockNum);
    std::string blockIndex(block);
    
    std::cout << "storage write path: " << (m_storagePath + blockIndex).c_str() << "\n";

    int fd = 0;
    if (-1 == (fd = open((m_storagePath + blockIndex).c_str(), O_CREAT | O_RDWR, 0644)))
    {
        return 1;
    }
    
    int write_bytes;
    if (-1 == (write_bytes = write(fd, data, protocol::BLOCK_SIZE)))
    {
        return 1;
    }
    std::cout << "write bytes in storage: " << write_bytes << "\n";
    
    if (-1 == close(fd))
    {
        return 1;
    }
    

    //memcpy(m_storage + (blockNum * protocol::BLOCK_SIZE), data, protocol::BLOCK_SIZE);

    return 0;
}

} // namespace ilrd


