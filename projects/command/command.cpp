/*******************************
    Yonatan Zaken
    Command
    CPP
    ILRD - RD8081               
*******************************/

#include "command.hpp"


namespace ilrd
{

/************************************ Read *********************************/

Read::Read(const boost::shared_ptr<Storage>& storage):
    m_storage(storage)
{

}

int Read::Operation()
{
    m_storage->Read();
}

boost::shared_ptr<Read> Read::CreateRead(const Message& message)
{

}

/************************************ Write *********************************/

Write::Write(const boost::shared_ptr<Storage>& storage):
    m_storage(storage)
{

}

int Write::Operation()
{
    m_storage->Write();
}

boost::shared_ptr<Write> Write::CreateWrite(const Message& message)
{
    
}

} // namespace ilrd



