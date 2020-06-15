/*******************************
    Yonatan Zaken
    Protocol Consts
    HPP
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_PROTOCOL_CONSTS_HPP
#define ILRD_RD8081_PROTOCOL_CONSTS_HPP

#include <inttypes.h>

namespace ilrd
{

namespace protocol
{
    enum Operation
    {
        READ,
        WRITE,
        NUM_OF_OPERATIONS
    };
    
    enum Connection
    {
        CLIENT,
        SERVER
    };

    static const uint64_t BLOCK_SIZE = 4096;

    static const uint64_t REPLY_METADATA_SIZE = 2 * sizeof(uint8_t) + sizeof(uint64_t);

    static const uint8_t REPLY_READ_METADATA_SIZE = REPLY_METADATA_SIZE;

    static const uint8_t REPLY_WRITE_METADATA_SIZE = REPLY_READ_METADATA_SIZE;

    static const uint64_t REQUEST_METADATA_SIZE = sizeof(uint8_t) + 2 * sizeof(uint64_t);
    
    static const uint64_t REPLY_READ_SIZE = BLOCK_SIZE + REPLY_READ_METADATA_SIZE;
    
    static const uint64_t REPLY_WRITE_SIZE = REPLY_READ_METADATA_SIZE;

    static const uint64_t RECV_BLOCK_SIZE = BLOCK_SIZE + REQUEST_METADATA_SIZE;

    static const uint64_t OPERATION_TYPE_OFFSET = 0;
    static const uint64_t REQUEST_ID_OFFSET = 1;
    static const uint64_t BLOCK_ID_OFFSET = 9;
    static const uint64_t ERROR_CODE_OFFSET = 9;
    static const uint64_t READ_DATA_BLOCK_OFFSET = 10;
    static const uint64_t WRITE_DATA_BLOCK_OFFSET = 17;

} // namespace protocol

} // namespace ilrd

#endif 