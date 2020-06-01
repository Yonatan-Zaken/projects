/*******************************
    Yonatan Zaken
    Command
    CPP
    ILRD - RD8081               
*******************************/

#include <cstring>
#include <boost/make_shared.hpp>
#include "command.hpp"

namespace ilrd
{

/************************************ Read *********************************/

Read::Read(RequestMessage& message):
    m_blockNum(message.GetBlockID()),
    m_buffer(message.DataBlock())
{
}

int Read::Operation(const boost::shared_ptr<Storage>& storage)
{
    return storage->Read(m_buffer, m_blockNum);
}

boost::shared_ptr<Read> Read::CreateRead(RequestMessage& message)
{
    return (boost::shared_ptr<Read>(new Read(message)));
}

/************************************ Write *********************************/

Write::Write(RequestMessage& message):
    m_blockNum(message.GetBlockID())
{
    memcpy(m_data, message.DataBlock(), protocol::BLOCK_SIZE);
}

int Write::Operation(const boost::shared_ptr<Storage>& storage)
{
    return storage->Write(m_data, m_blockNum);
}

boost::shared_ptr<Write> Write::CreateWrite(RequestMessage& message)
{
    return (boost::shared_ptr<Write>(new Write(message)));
}

} // namespace ilrd



