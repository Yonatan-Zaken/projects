/*********************
    NBDCommunicator
    Header File
    01/06/2020
    ILRD - RD8081           
*********************/
#ifndef ILRD_RD8081_NBDCOMMUNICATOR_HPP
#define ILRD_RD8081_NBDCOMMUNICATOR_HPP

namespace ilrd
{


class NBDCommunicator
{
public:	
    explicit NBDCommunicator();	
    NBDCommunicator(const NBDCommunicator& other);	
    NBDCommunicator& operator=(const NBDCommunicator& other);	
    ~NBDCommunicator();

    void SendTo();
    void RecvFrom();

private:
    int m_fdl
};

class Master
{
public:
    Master();
    ~Master();
private:
    Reactor& m_reactor;
};


} // namespace ilrd


#endif // ILRD_RD8081_NBDCOMMUNICATOR_HPP
