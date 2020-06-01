/*******************************
    Yonatan Zaken
    Command
    HPP
    ILRD - RD8081               
*******************************/

#ifndef ILRD_RD8081_COMMAND_HPP
#define ILRD_RD8081_COMMAND_HPP

#include <boost/shared_ptr.hpp>
#include "storage.hpp"
#include "message.hpp"

namespace ilrd
{

class Command
{
public:
    //explicit Command() = default;
    virtual ~Command() {}
    virtual int Operation(const boost::shared_ptr<Storage>& storage) = 0;
private:    
};

/******************************************************************************/

class Read: public Command
{
public:
    explicit Read(RequestMessage& message);
    // ~Read() = default;
    // Read(const Read&) = default;
    // Read& operator=(const Read&) = default;
    virtual int Operation(const boost::shared_ptr<Storage>& storage);
    static boost::shared_ptr<Read> CreateRead(RequestMessage& message);
private:
    uint64_t m_blockNum;
    uint8_t *m_buffer;
};

/******************************************************************************/

class Write: public Command
{
public:
    explicit Write(RequestMessage& message);
    // ~Write() = default;
    // Write(const Write&) = default;
    // Write& operator=(const Write&) = default;
    virtual int Operation(const boost::shared_ptr<Storage>& storage);
    static boost::shared_ptr<Write> CreateWrite(RequestMessage& message);
private:
    uint64_t m_blockNum;
    uint8_t m_data[protocol::BLOCK_SIZE];
};

} // namespace ilrd

#endif