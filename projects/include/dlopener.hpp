/*******************************
    Yonatan Zaken
    DLOpener
    HPP
    ILRD - RD8081               
*******************************/
#ifndef ILRD_RD8081_DLOPENER_HPP
#define ILRD_RD8081_DLOPENER_HPP

#include "utility.hpp"
#include "dispatcher.hpp"
#include "dirmonitor.hpp"
#include "plugin_manager.hpp"

namespace ilrd
{

class DLOpener
{
public:
    explicit DLOpener(const char *pluginPath, Framework& framework);
    //DLOpener(const DLOpener& other) = default;
    //DLOpener& operator=(const DLOpener& other) = default;	
    //~DLOpener() noexcept = default;
private:
    const char *m_pluginPath;
    Framework& m_framework;
    PluginManager m_pluginManager;
    Observer<InotifyEvent> m_observer;

    void UpdateFunc(InotifyEvent event);
    void DeathFunc();
};

} // namespace ilrd

#endif // ILRD_RD8081_DLOPENER_HPP
