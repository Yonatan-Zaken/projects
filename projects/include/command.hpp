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

namespace ilrd
{

class Command
{
public:
    //explicit Command() = default;
    virtual ~Command() {}
    virtual int Operation() = 0;
private:    
};

/******************************************************************************/

class Read: public Command
{
public:
    explicit Read(const boost::shared_ptr<Storage>& storage);
    // ~Read() = default;
    // Read(const Read&) = default;
    // Read& operator=(const Read&) = default;
    virtual int Operation();
    static boost::shared_ptr<Read> CreateRead(const Message& message);
private:
    boost::shared_ptr<Storage> m_storage;
};

/******************************************************************************/

class Write: public Command
{
public:
    explicit Write(const boost::shared_ptr<Storage>& storage)
    // ~Write() = default;
    // Write(const Write&) = default;
    // Write& operator=(const Write&) = default;
    virtual int Operation();
    static boost::shared_ptr<Write> CreateWrite(const Message& message);
private:
    boost::shared_ptr<Storage> m_storage;
}

} // namespace ilrd


#endif