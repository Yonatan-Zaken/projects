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
#include "framework.hpp"
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
    PluginManager m_pluginManager;
    Framework& m_framework;
    Observer<InotifyEvent> m_observer;
};

} // namespace ilrd

#endif // ILRD_RD8081_DLOPENER_HPP
