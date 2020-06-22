/*******************************
    Yonatan Zaken
    DLOpener
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_DLOPENER_HPP
#define ILRD_RD8081_DLOPENER_HPP

#include "observer.hpp"

namespace ilrd
{

class DLOpener
{
public:	
    explicit DLOpener(Dispatcher *dispatcher);	
    //DLOpener(const DLOpener& other) = default;	
    //DLOpener& operator=(const DLOpener& other) = default;	
    ~DLOpener() noexcept;
private:
    Observer<> m_observer;
};

} // namespace ilrd

#endif // ILRD_RD8081_DLOPENER_HPP
