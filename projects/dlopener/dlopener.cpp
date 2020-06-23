/*******************************
    Yonatan Zaken
    DLOpener
    CPP
    ILRD - RD8081               
*******************************/

#include "dlopener.hpp"

namespace ilrd
{

/************************** DLOpener Definitions ******************************/

DLOpener::DLOpener(const char *pluginPath, Framework& framework):
    m_pluginManager(pluginPath, framework),
    m_framework(framework),
    m_observer(m_framework.Get("dispatcher"), UpdateFunc, DeathFunc)
{
}

/******************************************************************************/

DLOpener::~DLOpener() noexcept
{
}

/******************************************************************************/

void DLOpener::UpdateFunc(InotifyEvent event)
{
    if (InotifyEvent::CREATE == event.operation)
    {
        m_pluginManager.Add(event.name, )
    }
    
    else
    {
        m_pluginManager.Remove(event.name);
    }
    
    
}

/******************************************************************************/

void DLOpener::DeathFunc()
{

}

} // namespace ilrd


