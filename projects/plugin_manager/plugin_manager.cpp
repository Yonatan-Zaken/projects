/*******************************
    Yonatan Zaken
    Plugin Manager
    CPP
    ILRD - RD8081               
*******************************/
#include <boost/shared_ptr.hpp>

#include "boost/filesystem.hpp"
#include "plugin_manager.hpp"

namespace ilrd
{

PluginManager::PluginManager(const char *pluginPath, Framework& framework):
    m_framework(framework),
    m_pluginList()
{
    boost::filesystem::path path(pluginPath);
    boost::filesystem::directory_iterator end_itr;

    for (boost::filesystem::directory_iterator itr(path); itr != end_itr; ++itr)
    {
        boost::shared_ptr<Plugin> plugin(new Plugin(m_framework, itr->path().c_str()));
        m_pluginList[itr->path().string()] = plugin;
    }
    
}

void PluginManager::Add(std::string pluginName, plugin_t plugin)
{
    m_pluginList[pluginName] = plugin;
}

void PluginManager::Remove(std::string pluginName)
{
    m_pluginList.erase(pluginName);
}

} // namespace ilrd


