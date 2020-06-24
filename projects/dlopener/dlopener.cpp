/*******************************
    Yonatan Zaken
    DLOpener
    CPP
    ILRD - RD8081               
*******************************/
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include "plugin.hpp"
#include "dlopener.hpp"

namespace ilrd
{

/************************** DLOpener Definitions ******************************/

DLOpener::DLOpener(const char *pluginPath, Framework& framework):
    m_pluginPath(pluginPath),
    m_framework(framework),
    m_pluginManager(pluginPath, framework),
    m_observer(m_framework.Get<DirMonitor *>("dirmonitor"), boost::bind(&DLOpener::UpdateFunc, this, _1), boost::bind(&DLOpener::DeathFunc, this))
{
}

/******************************************************************************/

void DLOpener::UpdateFunc(InotifyEvent event)
{
    std::string path(m_pluginPath);
    if (InotifyEvent::CREATE == event.operation)
    {
        boost::shared_ptr<Plugin> plugin(new Plugin(m_framework, (path + event.name).c_str()));
        m_pluginManager.Add(path + event.name, plugin);
    }
    
    else if (InotifyEvent::DELETE == event.operation)
    {
        m_pluginManager.Remove(path + event.name);
    }
}

/******************************************************************************/

void DLOpener::DeathFunc()
{
}

} // namespace ilrd


